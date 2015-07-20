#include "PowerControl.h"

void power_initial(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//PB
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//PC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	//PD
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}


int BatteryC_vol(void)
{
	u8 vol=0;
	
	return vol;
}

int BatteryD_vol(void)
{
	u8 vol=0;
	
	return vol;
}
