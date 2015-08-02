/**
  ******************************************************************************
  * @file    main.c
  * $Author: wdluo $
  * $Revision: 67 $
  * $Date:: 2012-08-15 19:00:29 +0800 #$
  * @brief   ������.
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

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[2];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ			 

float ADC_ConvertedValueLocal;  

//#define    MI_ERR    (-2)




void Delay(__IO u32 nCount);
void USBDataGet(uint8_t data[64],uint8_t BrailleDots[40],uint8_t InPacket[2]);
/**
  * @brief  ���ڴ�ӡ���
  * @param  None
  * @retval None
  */
int main(void)
{
	uint8_t data[64],BrailleDots[40],InPacket[2];
	uint32_t i=0,ret=0,voltemp;
/************************ϵͳ��ʼ������*****************************/
	Set_System();//ϵͳʱ�ӳ�ʼ��
	power_initial(); //��Դ���ƹܽų�ʼ��
	USART_Configuration();//����1��ʼ��
  GP_initial();        //MCU���ڳ�ʼ��
	blooth_initial();    //�������ڳ�ʼ��
	delay_init();        //��ʱ������ʼ��
	NVIC_Configuration(); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	OLED_Init();			//��ʼ��OLED     
	ADC1_Init();      //��ʼ��ADC1
	//USB��ʼ��
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();
	        
/*******************************************************************/
	Board_ON();//������������
	Blooth_Down();  //��ʼ���ر�����
	GP_Down();      //��ʼ���ر�51��Ƭ��
	IDrive_Down();  //��ʼ���رպ���Դ
	 OLED_Clear();	 //ˢ��
		 // OLED_ShowString(0,0, "DAISY IS HOT");  //�ַ�����ʾ
	 OLED_ShowString(0,0, "Welcome to BD");
	 OLED_ShowString(0,2, "Starting...");
	delay_ms(1000);
	EXTI_PD2_Config(); //KEY�ⲿ�жϼ��
	EXTI_PD3_Config(); //�ػ����
	//printf("\x0c\0");printf("\x0c\0");//�����ն�����
	//printf("\033[1;40;32m");//���ó����ն˱���Ϊ��ɫ���ַ�Ϊ��ɫ
  //��������
	printf("\r\n*******************************************************************************");
	printf("\r\n************************ Copyright 2009-2012, ViewTool ************************");
	printf("\r\n*************************** http://www.viewtool.com ***************************");
	printf("\r\n***************************** All Rights Reserved *****************************");
	printf("\r\n*******************************************************************************");
	printf("\r\n");
  /*****************OLED��ʾ*******************/
		
		 delay_ms(3000);
		 OLED_Clear();	 //ˢ��
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
		
/******************USB��Ϣ��ѯ*********************/
		USBDataGet(data,BrailleDots,InPacket);
	
	/****************************************************/	
	  if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))
			OLED_ShowString(0,0,"DISCHARGING");
		else
			OLED_ShowString(0,0,"CHARGING");
	/***************��ص�ѹ���******************/
    	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue[1]/2048*3.3*1.07; // ��ȡת����ADֵ��
			printf("\r\n The PC4 current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The PC4 current AD value = %f V \r\n",ADC_ConvertedValueLocal); 	
      OLED_ShowString(0,4,"ICPOWER=");
	    voltemp=ADC_ConvertedValueLocal*1000;
	    OLED_ShowNum(64,4,voltemp,4,16);
	    OLED_ShowString(100,4,"mv");
	    ADC_ConvertedValueLocal =(float) ADC_ConvertedValue[0]/2048*3.3*1.08;// ��ȡת����ADֵ��
			printf("\r\n The PC5 current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The PC5 current AD value = %f V \r\n",ADC_ConvertedValueLocal); 
		  OLED_ShowString(0,6,"SYSPOWER=");
	    voltemp=ADC_ConvertedValueLocal*1000;
	    OLED_ShowNum(72,6,voltemp,4,16);
	    OLED_ShowString(108,6,"mv");
/****************************************************************/	
	/**********************������ӡ����***********************/
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
	
	
		
			/*****************��λ*********************/
		 
	}
}
/**************�����ⲿ�жϴ���**************/
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
void Delay(__IO u32 nCount)	 //�򵥵���ʱ����
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
  * @brief  �����ڼ�������������ʱ��Դ�ļ����ʹ�������
  * @param  file Դ�ļ���
  * @param  line ������������ 
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* �û����������Լ��Ĵ������ڱ��������ļ�������������,
       ���磺printf("�������ֵ: �ļ��� %s �� %d��\r\n", file, line) */

    /* ����ѭ�� */
    while (1)
    {
    }
}
#endif

/*********************************END OF FILE**********************************/
