/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     zhi.xin       the first version
 */
#ifndef APPLICATIONS_USART1_USART1_H_
#define APPLICATIONS_USART1_USART1_H_

#include "stm32f4xx_conf.h"
#include "stdio.h"

extern uint8_t ucTemp;

#define USART1_TX_PIN GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10
#define USART1_TX_PORT GPIOA
#define USART1_RX_PORT GPIOA

#define USART1_BAUDRATE 9600

void usart1_Init(void);
void Usart_SendByte(USART_TypeDef * pUSARTx,uint8_t ch);
void Usart_SendString(USART_TypeDef * pUSARTx,char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
int fputc(int ch,FILE *f);


#endif /* APPLICATIONS_USART1_USART1_H_ */
