
#include "exti.h"

/*
 * ��������NVIC_Configuration
 * ����  ������Ƕ�������жϿ�����NVIC
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* ����P[A|B|C|D|E]2Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������EXTI_PD2_Config
 * ����  ������ PD2 Ϊ���жϿڣ��������ж����ȼ�
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void EXTI_PD2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline(PD2) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);

	/* config the NVIC(PD2) */
	NVIC_Configuration();

	/* EXTI line gpio config(PD2) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* EXTI line(PD2) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource2); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

