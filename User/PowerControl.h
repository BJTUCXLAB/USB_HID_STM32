#ifndef __POWERCONTROL_H
#define __POWERCONTROL_H

#include "stm32f10x.h"
#include <stdio.h>

#define Blooth_Down() GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define Blooth_ON() GPIO_SetBits(GPIOC,GPIO_Pin_6)
#define Board_ON() GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define Board_Down() GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define IDrive_ON()  GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define IDrive_Down() GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define GP_ON() GPIO_SetBits(GPIOC,GPIO_Pin_7)
#define GP_Down() GPIO_ResetBits(GPIOC,GPIO_Pin_7)

int BatteryC_vol(void);
int BatteryD_vol(void);
void power_initial(void);
#endif /* __USART3_H */
