/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     zhi.xin       the first version
 */
#ifndef APPLICATIONS_KEY_KEY_H_
#define APPLICATIONS_KEY_KEY_H_
#include "stm32f4xx_conf.h"

#define key1_pin    GPIO_Pin_0
#define key1_port   GPIOA

#define key2_pin    GPIO_Pin_13
#define key2_port   GPIOC

void key1_Init(void);
void key2_Init(void);

uint8_t Get_Key1(void);
uint8_t Get_Key2(void);
#endif /* APPLICATIONS_KEY_KEY_H_ */
