/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-03     RT-Thread    first version
 */

#include <stdio.h>
#include <board.h>

#include "stm32f4xx_conf.h"



void init(void);
void NVIC_Configuration(void);

uint8_t ucTemp; //全局变量

int main(void)
{
    init();
    NVIC_Configuration();

    LED2_ON;
    wait_ms(1000);
    LED2_OFF;
    wait_ms(1000);

    Usart_SendString( USART1,"this is a expriment\r\n");
    wait_ms(100);
    printf("123\n");


    char ch = 0;
    while (1)
    {
        wait_ms(1000);
        LED3_OFF;
        if(ucTemp == 0){

            ucTemp &= 0x00;
            LED3_ON;
        }
        printf("this is a expriment:%lX\n",ucTemp);
    }
    return 0;
}
//待办事项：
//clock_information 改写函数

void init(void){
    LED_GPIO_Config();
    key1_Init();
    key2_Init();
    SysTick_Init();
    Exti_Config();
    usart1_Init();
//    Debug_USART_Config();
//    uart_init(90,115200);   //??????115200
}
void NVIC_Configuration(void){
    NVIC_InitTypeDef NVIC_InitStructure;
    /* ??????NVIC???????????????1 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* ????????????????????????1 */
    NVIC_InitStructure.NVIC_IRQChannel                      = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
    /* ????????????????????????1 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 1;
    /* ?????????????????????1 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
    NVIC_Init(&NVIC_InitStructure);

    //??????????????????
   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel                      = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
    NVIC_Init(&NVIC_InitStructure);

    /* ???????????????????????? */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    /* ???????????? */

}
