#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx.h"

#define DEBUG_USART_1                             USART1
#define DEBUG_USART_1_CLK                         RCC_APB2Periph_USART1
#define DEBUG_USART_1_BAUDRATE                    38400  //

/* F411CEU6 USART1 */
/* F411CEU6 只有 USART1、USART6 两个USART */
#define DEBUG_USART_1_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_1_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_1_TX_PIN                      GPIO_Pin_9
#define DEBUG_USART_1_TX_AF                       GPIO_AF_USART1
#define DEBUG_USART_1_TX_SOURCE                   GPIO_PinSource9

#define DEBUG_USART_1_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_1_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_1_RX_PIN                      GPIO_Pin_10
#define DEBUG_USART_1_RX_AF                       GPIO_AF_USART1
#define DEBUG_USART_1_RX_SOURCE                   GPIO_PinSource10



#define DEBUG_USART_6                             USART6
#define DEBUG_USART_6_CLK                         RCC_APB2Periph_USART6
#define DEBUG_USART_6_BAUDRATE                    9600  //串口波特率

/* F411CEU6 USART6 */
/* F411CEU6 只有 USART1、USART6 两个USART */
#define DEBUG_USART_6_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_6_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_6_TX_PIN                      GPIO_Pin_11//TX:A11
#define DEBUG_USART_6_TX_AF                       GPIO_AF_USART6
#define DEBUG_USART_6_TX_SOURCE                   GPIO_PinSource11

#define DEBUG_USART_6_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_6_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_6_RX_PIN                      GPIO_Pin_12//RX:A12
#define DEBUG_USART_6_RX_AF                       GPIO_AF_USART6
#define DEBUG_USART_6_RX_SOURCE                   GPIO_PinSource12

#define DEBUG_USART_6_IRQHandler                  USART6_IRQHandler  
#define DEBUG_USART_6_IRQ                 				USART6_IRQn


void Debug_USART_Config(void);
void uart3SendChars(uint8_t *str, uint16_t strlen);
void uart3SendChar(uint8_t ch);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);//16位
int8_t Receive(void);
void USART_GPIO_Init(void);


#endif


