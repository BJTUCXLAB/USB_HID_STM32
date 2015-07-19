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

#define CELL_COUNT 40

uint8_t GetKeynum;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t USB_Received_Flag;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值			 

float ADC_ConvertedValueLocal;  
/**
  * @brief  串口打印输出
  * @param  None
  * @retval None
  */
int main(void)
{
	uint8_t data[64],BrailleDots[40],InPacket[2];
	uint32_t i=0,ret=0;
	Set_System();//系统时钟初始化
	USART_Configuration();//串口1初始化
	//printf("\x0c\0");printf("\x0c\0");//超级终端清屏
	//printf("\033[1;40;32m");//设置超级终端背景为黑色，字符为绿色
	printf("\r\n*******************************************************************************");
	printf("\r\n************************ Copyright 2009-2012, ViewTool ************************");
	printf("\r\n*************************** http://www.viewtool.com ***************************");
	printf("\r\n***************************** All Rights Reserved *****************************");
	printf("\r\n*******************************************************************************");
	
	printf("\r\n");
/***************电池电压检测******************/
   	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值、
			printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

	                             
			ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值、
			printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();
	//OLED_Init();			//初始化OLED     
	ADC1_Init();      //初始化ADC1
	EXTI_PD2_Config(); //KEY外部中断检测
	
	while(1)
	{
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
				  InPacket[0]=0x81;
				  InPacket[1]=GetKeynum;
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
		
			
		
		/*****************OLED显示*******************/
		  //OLED_ShowString(0,0, "0.96' OLED TEST");  //字符串显示
			//	OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	 
			//	OLED_ShowNum(103,48,t,3,16);//显示ASCII字符的码值 
			//OLED_Refresh_Gram();	 //刷新
			
			
			//**************按键外部中断触发**************/
			/*****************复位*********************/
		 
	}
}
void EXTI2_IRQHandle(void)
{
	GetKeynum=GetKey();
	
}
void EXTI3_IRQHandle(void)
{
	printf("/r/n电压检测成功");
}

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
