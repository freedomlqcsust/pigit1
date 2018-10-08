#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "sys.h"

#define AD_Start_flag 	0x0001
#define uart_send_flag	0x0002

void  Adc_Init(void);
void Adc_Timer2_Init(void);

#endif
