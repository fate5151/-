#include "stm32f4xx.h"                  // Device header
#include "Serial.h"

uint8_t RxSTA;

//---------------------------------
//∑¢ÀÕ∂À¿∂—¿
//--------------------------------------

void HC05_Init()
{
	Serial_Init();
}

//void HC05_EnterAT()
//{
//	GPIO_SetBits(GPIOA, GPIO_Pin_0);
//}	

//void HC05_ExitAT()
//{
//	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
//}

void HC05_SendString(char *Buf)
{
	Serial_Printf(Buf);
}

void HC05_GetData(char *Buf)
{
	uint32_t count = 0, a = 0;
	while (count < 10000)
	{
		if (Serial_GetRxFlag() == 1)
		{
			Buf[a] = Serial_GetRxData();
			a ++;
			count = 0;
			RxSTA = 0;
		}
		count ++;
	}

}

void clearString(char * ch)
	{
while(*ch!='\0'){
*(ch++) = '\0';
}
}
