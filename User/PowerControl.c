#include "PowerControl.h"
void power_initial(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}
void Blooth_Down(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
}

void Blooth_ON(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
}

void Board_ON(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

void Board_Down(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}

void IDrive_ON(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void IDrive_Down(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void GP_ON(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_7);
}

void GP_Down(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
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
