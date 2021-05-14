#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "stm32f10x.h"

void Communication_Decode(void);
void Door_Waitopen(void);
void Led_ADC_Open(void);
void Led_ADC_Close(void);
void Door_ADC_Control(void);
void ADC_Local(void);

#endif /* __FUNCTION_H */
