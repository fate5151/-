#ifndef __ADC_H
#define __ADC_H

void ADC_DMA_Config(void);
u16 Get_Adc_Average(u8 ch,u8 times);
u16 Get_Adc(u8 ch)   ;

extern uint16_t ADC_Buffer[10];


#endif
