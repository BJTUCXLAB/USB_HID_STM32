#ifndef __POWERCONTROL_H
#define __POWERCONTROL_H
#include "stm32f10x.h"
#include <stdio.h>

void Blooth_Down(void);
void Blooth_ON(void);
void Board_ON(void);
void Board_Down(void);
void IDrive_ON(void);
void IDrive_Down(void);
void GP_ON(void);
void GP_Down(void);
int BatteryC_vol(void);
int BatteryD_vol(void);

#endif /* __USART3_H */
