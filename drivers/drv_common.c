/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-20     chenyaxing   first version
 */

#include <stm32f4xx.h>
#include "stm32f4xx_conf.h"
extern int rt_hw_usart_init();
extern void system_clock_config(int);
extern int clock_information(void);

void clk_init(char *clk_source, int source_freq, int target_freq)
{
//    HAL_Init();
//
//    /* disbale interrupt */
//    __set_PRIMASK(1);
//    /* system clock config */
//    system_clock_config(target_freq);
//    /* init system tick to 1KHz */
//#if defined (SOC_SERIES_STM32H7)
//    HAL_SYSTICK_Config((HAL_RCCEx_GetD1SysClockFreq()) / 1000);
//#else
//    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
//#endif
//    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
//    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
//    /* enable interrupt */
//    __set_PRIMASK(0);
}

//int uart_init()
//{
//    rt_hw_usart_init();
//    clock_information();
//    return 0;
//}




void SysTick_Handler(void)
{
//    HAL_IncTick();
    TimingDelay_Decrement();
}
void EXTI0_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        // LED1 取反
        LED1_TOGGLE;
    //清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
//
#if 0
void USART1_IRQHandler(void)
{
//    uint8_t ucTemp;
//    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//    {
//        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//        ucTemp = USART_ReceiveData(USART1);
//        USART_SendData(USART1, ucTemp);
//    }
//    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收到数据
//    {
//        uart_receive=0;//蓝牙接收相关变量
//        uart_receive=USART_ReceiveData(USART1);
//    }
//    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//    {
//        /* Clear the USART1 Receive interrupt */
//        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//    }
//    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET)
//    {
//      USART_ClearFlag(USART1,USART_FLAG_ORE);
//      USART_ReceiveData(USART1);
//    }
    volatile uint8_t ucTemp = 0;

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {

        ucTemp = USART_ReceiveData( USART1 );
        USART_SendData(USART1,ucTemp);

        //uart_receive=0;//蓝牙接收相关变量
        //uart_receive=USART_ReceiveData(USART1);
        //LED3_ON;
    }
}
#endif
void _error_handler(char *s, int num)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    while (1)
    {
    }
    /* USER CODE END Error_Handler */
}
