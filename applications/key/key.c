/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     zhi.xin       the first version
 */
#include "key.h"

void key1_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin     =   key1_pin;
    GPIO_InitStructure.GPIO_PuPd    =   GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed   =   GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode    =   GPIO_Mode_IN;
    GPIO_Init(key1_port, &GPIO_InitStructure);
}
void key2_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin     =   key2_pin;
    GPIO_InitStructure.GPIO_PuPd    =   GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed   =   GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode    =   GPIO_Mode_IN;
    GPIO_Init(key2_port, &GPIO_InitStructure);
}

uint8_t Get_Key1(void)
{
    return GPIO_ReadInputDataBit(key1_port, key1_pin);
}
uint8_t Get_Key2(void)
{
    return GPIO_ReadInputDataBit(key2_port, key2_pin);
}
