#include "bsp_adc.h"

void  Adc_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);													//使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);													//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 													//使能ADC1时钟

	//先初始化ADC1通道5 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;																			//PB0 通道0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;																	//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;															//不带上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);																				//初始化
	// GPIO_Init(GPIOB, &GPIO_InitStructure);																				//初始化

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);	 												//ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);													//复位结束


	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;											//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;	//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 			//DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;										//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz
	ADC_CommonInit(&ADC_CommonInitStructure);																			//初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;												//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;																	//非扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;														//关闭连续转换
//	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;		//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;					//
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;												//右对齐
	ADC_InitStructure.ADC_NbrOfConversion = 1;																		//1个转换在规则序列中 也就是只转换规则序列1



	ADC_Init(ADC1, &ADC_InitStructure);																						//ADC初始化

	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_56Cycles);
	ADC_Cmd(ADC1, ENABLE);																												//开启AD转换器

}

void Adc_Timer2_Init(void)
{
	// 定时器时钟源TIMxCLK = 2 * PCLK1
	// PCLK1 = HCLK / 4
	// => TIMxCLK=HCLK/2=SystemCoreClock/2=84MHz
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//定时器中断设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //定时器TIM2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;       //子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);    //根据指定的参数初始化NVIC寄存器

	// 使能Timer2的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// 使能Timer2
	TIM_Cmd(TIM2, DISABLE);
	// 初始化定时器
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	// 定时器计数周期84MHz/105=800kHz
	TIM_TimeBaseStructure.TIM_Prescaler = 105 - 1;
	// 向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// 计数值
	TIM_TimeBaseStructure.TIM_Period = 10 - 1;
	// 时钟分频因子 0
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// 初始化定时器2
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// 允许TIM2定时重载
	// TIM_ARRPreloadConfig(TIM2, ENABLE);
	// 选择TIM2的UPDATA事件更新为触发源
	// TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	// 使能定时器
//	TIM_Cmd(TIM2, ENABLE);
}

