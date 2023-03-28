/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-28     zhi.xin       the first version
 */
#include "delay.h"
 /**************************************************************************
 作  者 ：大鱼电子
淘宝地址：https://shop119207236.taobao.com
**************************************************************************/

static u8  fac_us=0;                            //us延时倍乘数
static u16 fac_ms=0;                            //ms延时倍乘数,在ucos下,代表每个节拍的ms数

void delay_init()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //选择外部时钟  HCLK/8
    fac_us=SystemCoreClock/8000000;             //为系统时钟的1/8
    fac_ms=(u16)fac_us*1000;                    //非OS下,代表每个ms需要的systick时钟数
}
//延时nus
//nus为要延时的us数.
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD=nus*fac_us;                   //时间加载
    SysTick->VAL=0x00;                          //清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;    //开始倒数
    do
    {
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));       //等待时间到达
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;    //关闭计数器
    SysTick->VAL =0X00;                          //清空计数器
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD=(u32)nms*fac_ms;              //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL =0x00;                         //清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;    //开始倒数
    do
    {
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));       //等待时间到达
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;    //关闭计数器
    SysTick->VAL =0X00;                         //清空计数器
}



/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
  *          常用的有 1us 10us 1ms 中断。
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

//#include "./systick/bsp_SysTick.h"

static __IO u32 TimingDelay;

/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
    /* SystemFrequency / 1000    1ms中断一次
     * SystemFrequency / 100000  10us中断一次
     * SystemFrequency / 1000000 1us中断一次
     */
    if (SysTick_Config(SystemCoreClock / 10000))
    {
        /* Capture error */

        while (1);
    }
}

/**
  * @brief   us延时程序,10us为一个单位
  * @param
  *     @arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
  * @retval  无
  */
void Delay_us(__IO u32 nTime)
{
    TimingDelay = nTime;

    while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}
/*********************************************END OF FILE**********************/
