/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-28     zhi.xin       the first version
 */
#ifndef APPLICATIONS_DELAY_DELAY_H_
#define APPLICATIONS_DELAY_DELAY_H_

#include "stm32f4xx_conf.h"
//大鱼电子实现
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

//野火实现方式
#include "stm32f4xx.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);
#define Delay_ms(x) Delay_us(10*x)  //µ¥Î»ms
void TimingDelay_Decrement(void);

#endif /* APPLICATIONS_DELAY_DELAY_H_ */
