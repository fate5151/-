#include "bsp_debug_usart.h"
#include "string.h"
#include "stdlib.h"  
#include "stm32f4xx.h"                  // Device header




void Debug_USART_Config()
{  
	//GPIO Peripherals Configuration 
  GPIO_InitTypeDef 	GPIO_InitStructure;
	
	//USART Peripherals Configuration 
	USART_InitTypeDef USART_InitStructure;
	
	//GPIO Clock Configuration
	RCC_AHB1PeriphClockCmd(DEBUG_USART_1_TX_GPIO_CLK | DEBUG_USART_1_RX_GPIO_CLK,ENABLE); 
  
	//USART which we use Clock Configuration
	RCC_APB2PeriphClockCmd(DEBUG_USART_1_CLK,ENABLE); 
	
	//the usart we use need AF configuration
	GPIO_PinAFConfig(DEBUG_USART_1_TX_GPIO_PORT, DEBUG_USART_1_TX_SOURCE, DEBUG_USART_1_TX_AF);  
	GPIO_PinAFConfig(DEBUG_USART_1_RX_GPIO_PORT, DEBUG_USART_1_RX_SOURCE, DEBUG_USART_1_RX_AF); 
	
	//USART's GPIO peripherals registers' configuration
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_1_TX_PIN | DEBUG_USART_1_RX_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   
	
	//write data in the registers
	GPIO_Init(GPIOA , &GPIO_InitStructure);          
  

	//USART which we use registers' configuration
	USART_InitStructure.USART_BaudRate 						= DEBUG_USART_1_BAUDRATE;
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;  
	USART_InitStructure.USART_Parity 							= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;	
  
	//USART which we use init
	USART_Init(DEBUG_USART_1, &USART_InitStructure); 
	
	//NVIC_Configuration();
		
	USART_ClearFlag(DEBUG_USART_1, USART_FLAG_TC);
	
	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      
	
	//enable the USART which we use
	USART_Cmd(DEBUG_USART_1, ENABLE);  
	
	
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* 抢断优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	
}


/*****************  send a char **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* send a bute to the USART */
	USART_SendData(pUSARTx,ch);
		
	/* wait for the register which sends data to be empty */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  send string **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* wait for send completely */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE)==RESET)
  {}
}

/*****************  send a 16 bits data **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* take out the high 8 bits */
	temp_h = (ch&0XFF00)>>8;
	/* take out the low 8 bits */
	temp_l = ch&0XFF;
	
	/* send the high 8 bits */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* send the low 8 bits */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

//Redirect the C library function printf to the USART, \
  and use the printf() function after resetting
//int fputc(int ch, FILE *f)
//{
//		/* send a byte to the usart */
//		USART_SendData(DEBUG_USART_6, (uint8_t) ch);
//		
//		/* wait for send data completely */
//		while (USART_GetFlagStatus(DEBUG_USART_6, USART_FLAG_TXE) == RESET);		
//	
//		return (ch);
//}

//Redirect the C library function scanf to the USART, so that we can \
  we can use scanf() function, or putchar()
int fgetc(FILE *f)
{
		/* wait for the data come from the USART */
		while (USART_GetFlagStatus(DEBUG_USART_6, USART_FLAG_RXNE) == RESET);
		return (int)USART_ReceiveData(DEBUG_USART_6);
}



int8_t Receive(void)
{
	int8_t RX_DATA;
		if(USART_GetFlagStatus(USART6,USART_FLAG_RXNE)==SET) 
   {
			RX_DATA=USART_ReceiveData(USART6); 
//			Usart_SendByte(USART6,Rx_state);
//			OLED_ShowHexNum(4,1,RX_DATA,3);
	//	 USART_ClearITPendingBit(USART6,USART_IT_RXNE);
   }
	 return RX_DATA;
}



