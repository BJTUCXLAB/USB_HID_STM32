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

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ			 

float ADC_ConvertedValueLocal;  
/**
  * @brief  ���ڴ�ӡ���
  * @param  None
  * @retval None
  */
int main(void)
{
	uint8_t data[64],BrailleDots[40],InPacket[2];
	uint32_t i=0,ret=0;
	Set_System();//ϵͳʱ�ӳ�ʼ��
	USART_Configuration();//����1��ʼ��
	//printf("\x0c\0");printf("\x0c\0");//�����ն�����
	//printf("\033[1;40;32m");//���ó����ն˱���Ϊ��ɫ���ַ�Ϊ��ɫ
	printf("\r\n*******************************************************************************");
	printf("\r\n************************ Copyright 2009-2012, ViewTool ************************");
	printf("\r\n*************************** http://www.viewtool.com ***************************");
	printf("\r\n***************************** All Rights Reserved *****************************");
	printf("\r\n*******************************************************************************");
	
	printf("\r\n");
/***************��ص�ѹ���******************/
   	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ��
			printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

	                             
			ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ��
			printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
	   	printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();
	//OLED_Init();			//��ʼ��OLED     
	ADC1_Init();      //��ʼ��ADC1
	EXTI_PD2_Config(); //KEY�ⲿ�жϼ��
	
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
		
			
		
		/*****************OLED��ʾ*******************/
		  //OLED_ShowString(0,0, "0.96' OLED TEST");  //�ַ�����ʾ
			//	OLED_ShowChar(48,48,t,16,1);//��ʾASCII�ַ�	 
			//	OLED_ShowNum(103,48,t,3,16);//��ʾASCII�ַ�����ֵ 
			//OLED_Refresh_Gram();	 //ˢ��
			
			
			//**************�����ⲿ�жϴ���**************/
			/*****************��λ*********************/
		 
	}
}
void EXTI2_IRQHandle(void)
{
	GetKeynum=GetKey();
	
}
void EXTI3_IRQHandle(void)
{
	printf("/r/n��ѹ���ɹ�");
}

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
