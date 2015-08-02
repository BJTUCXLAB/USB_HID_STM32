#ifndef __USART3_H
#define	__USART3_H

#include "stm32f10x.h"
#include <stdio.h>

void GP_initial(void);
void GP_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif /* __USART3_H */
