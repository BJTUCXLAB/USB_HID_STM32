/**
  ******************************************************************************
  * @file    main.c
  * $Author: wdluo $
  * $Revision: 67 $
  * $Date:: 2012-08-15 19:00:29 +0800 #$
  * @brief   主函数.
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "usart.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usbio.h"
#include "oled.h"
#include "51GP.h"
#include "blooth.h"
#include "adc.h"
#include "keyscan.h"
#include "exti.h"
#include "PowerControl.h"
#include "delay.h"
#include "bmp.h"
#define CELL_COUNT 40

uint8_t GetKeynum;
int keynum=0;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t USB_Received_Flag;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[2];

// 局部变量，用于保存转换计算后的电压值			 

float ADC_ConvertedValueLocal;  

//#define    MI_ERR    (-2)




void Delay(__IO u32 nCount);
void USBDataGet(uint8_t data[64],uint8_t BrailleDots[40],uint8_t InPacket[2]);
/**
  * @brief  串口打印输出
  * @param  None
  * @retval None
  */
int main(void)
{
	uint8_t data[64],BrailleDots[40],InPacket[2];
	uint32_t i=0,ret=0,voltemp;
/************************系统初始化函数*****************************/
	Set_System();//系统时钟初始化
	power_initial(); //电源控制管脚初始化
	USART_Configuration();//串口1初始化
  GP_initial();        //MCU串口初始化
	blooth_initial();    //蓝牙串口初始化
	delay_init();        //延时函数初始化
	NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	OLED_Init();			//初始化OLED     
	ADC1_Init();      //初始化ADC1
	//USB初始化
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();
	        
/*******************************************************************/
	Board_ON();//板载自锁供电
	Blooth_Down();  //初始化关闭蓝牙
	GP_Down();      //初始化关闭51单片机
	IDrive_Down();  //初始化关闭恒流源
	 OLED_Clear();	 //刷新
		 // OLED_ShowString(0,0, "DAISY IS HOT");  //字符串显示
	 OLED_ShowString(0,0, "Welcome to BD");
	 OLED_ShowString(0,2, "Starting...");
	delay_ms(1000);
	EXTI_PD2_Config(); //KEY外部中断检测
	EXTI_PD3_Config(); //关机检测
	//printf("\x0c\0");printf("\x0c\0");//超级终端清屏
	//printf("\033[1;40;32m");//设置超级终端背景为黑色，字符为绿色
  //开机测试
	printf("\r\n*******************************************************************************");
	printf("\r\n************************ Copyright 2009-2012, ViewTool ************************");
	printf("\r\n*************************** http://www.viewtool.com ***************************");
	printf("\r\n***************************** All Rights Reserved *****************************");
	printf("\r\n*******************************************************************************");
	printf("\r\n");
  /*****************OLED显示*******************/
		
		 delay_ms(3000);
		 OLED_Clear();	 //刷新
		 OLED_ShowString(0,0,"DISCHARGING...");  
		 delay_ms(3000);
		 //OLED_DrawBMP(0,0,128,8,gImage_daisy);
		 //delay_ms(3000);
	//	 blooth_printf(USART2,"blooth is OK");
		//GP_printf
			 OLED_Clear();
	/***********************************************/
 // GPIO_SetBits(GPIOE,GPIO_Pin_3);
	while(1)
	{
		
/******************USB消息轮询*********************/
		USBDataGet(data,BrailleDots,InPacket);
	
	/****************************************************/	
	  if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))
			OLED_ShowString(0,0,"DISCHARGING");
		else
			OLED_ShowString(0,0,"CHARGING");
	/***************电池电压检测******************/
    	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue[1]/2048*3.3*1.07; // 读取转换的AD值、
			printf("\r\n The PC4 current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The PC4 current AD value = %f V \r\n",ADC_ConvertedValueLocal); 	
      OLED_ShowString(0,4,"ICPOWER=");
	    voltemp=ADC_ConvertedValueLocal*1000;
	    OLED_ShowNum(64,4,voltemp,4,16);
	    OLED_ShowString(100,4,"mv");
	    ADC_ConvertedValueLocal =(float) ADC_ConvertedValue[0]/2048*3.3*1.08;// 读取转换的AD值、
			printf("\r\n The PC5 current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The PC5 current AD value = %f V \r\n",ADC_ConvertedValueLocal); 
		  OLED_ShowString(0,6,"SYSPOWER=");
	    voltemp=ADC_ConvertedValueLocal*1000;
	    OLED_ShowNum(72,6,voltemp,4,16);
	    OLED_ShowString(108,6,"mv");
/****************************************************************/	
	/**********************蓝牙打印测试***********************/
	   blooth_printf(USART2,"\r\nblooth is ok!\r\n");
	   GP_printf(USART3,"\r\nMCU Connect\r\n");
/****************************************************************/	
//	 IDrive_ON();
//		  printf("\r\nIC on");
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
//		  IDrive_Down();
			
//		  printf("\r\nIC down");
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
			Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);
		  Delay(0x0FFFEF);	
			//GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	
	
		
			/*****************复位*********************/
		 
	}
}
/**************按键外部中断触发**************/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line15)!=RESET)
	{
	//GetKeynum=GetKey();
	printf("/r/nkeyget");
  OLED_ShowString(0,0,"getkey");
	OLED_ShowNum(50,0,keynum,2,16);
		keynum++;
		if(keynum%2)
		{
			IDrive_Down();
			GP_Down();
			Blooth_Down();
    }
		else
		{
			IDrive_ON();
			GP_ON();
			Blooth_ON();
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line15);
}
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
	{
	OLED_Clear();
	OLED_ShowString(0,0,"shutdown");
		printf("/r/nshutdown");
	}
	 Board_Down();
	EXTI_ClearITPendingBit(EXTI_Line3);
}
/**************************************************/
void Delay(__IO u32 nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
} 
/**************************************************/
void USBDataGet(uint8_t data[64],uint8_t BrailleDots[40],uint8_t InPacket[2])
{
	   uint32_t i=0,ret=0;
			if(USB_Received_Flag){
			USB_Received_Flag=0;
			ret = USB_GetData(data,sizeof(data));
			//
			switch(data[0])
			{
				case 0x80:
				  for(i=0;i<CELL_COUNT;i++)
				  {BrailleDots[i]=data[i+1];}
					break;
				case 0x81:
				//  InPacket[0]=0x81;
				//  InPacket[1]=GetKeynum;
				  break;
				default:
					break;
      }
			printf("usb get data %d byte data\n\r",ret);
			for(i=0;i<ret;i++){
				printf("0x%02X ",data[i]);
			}
			printf("\n\r");
			USB_SendData(data,sizeof(data));
		}
}
/***************************************************/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  报告在检查参数发生错误时的源文件名和错误行数
  * @param  file 源文件名
  * @param  line 错误所在行数 
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* 用户可以增加自己的代码用于报告错误的文件名和所在行数,
       例如：printf("错误参数值: 文件名 %s 在 %d行\r\n", file, line) */

    /* 无限循环 */
    while (1)
    {
    }
}
#endif

/*********************************END OF FILE**********************************/
