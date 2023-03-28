/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-29     zhi.xin       the first version
 */
#include "usart1.h"


void usart1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
//时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//TX
    GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin    = USART1_TX_PIN;
    GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
    GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);
//RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
    GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);
//复用功能
    GPIO_PinAFConfig(USART1_TX_PORT, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(USART1_RX_PORT, GPIO_PinSource10, GPIO_AF_USART1);

    USART_InitStructure.USART_BaudRate              = USART1_BAUDRATE;
    USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity                = USART_Parity_No;
    USART_InitStructure.USART_StopBits              = USART_StopBits_1;
    USART_InitStructure.USART_WordLength            = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}
void Usart_SendByte(USART_TypeDef * pUSARTx,uint8_t ch)
{
    /* 发送一个字节数据到USART */
    USART_SendData(pUSARTx, ch);
    while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);
}
//发送字符串
void Usart_SendString(USART_TypeDef * pUSARTx,char *str)
{
    unsigned int k = 0;
    do
    {
        Usart_SendByte(pUSARTx,*(str+k));
        k++;
    }while(*(str + k)!='\0');
    while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE) == RESET);
}
/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
    uint8_t temp_h, temp_l;

    /* 取出高八位 */
    temp_h = (ch&0XFF00)>>8;
    /* 取出低八位 */
    temp_l = ch&0XFF;

    /* 发送高八位 */
    USART_SendData(pUSARTx,temp_h);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);

    /* 发送低八位 */
    USART_SendData(pUSARTx,temp_l);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
//#if 1
//#pragma import(__use_no_semihosting)
////标准库需要的支持函数
//
//struct __FILE
//{
//    int handle;
//
//};
//
//FILE __stdout;
////定义_sys_exit()以避免使用半主机模式
//_sys_exit(int x)
//{
//    x = x;
//}
//int _write(int fd, char *ptr, int len)
//{
////  HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 0xFFFF);
//  return len;
////      while((USART1->SR&0X40)==0);//循环发送,直到发送完毕
////      USART1->DR = (u8) ch;
////      return ch;
//}
//重定义fputc函数
//int fputc(int ch, FILE *f)
//{
//    while((USART1->SR&0X40)==0);//循环发送,直到发送完毕
//    USART1->DR = (u8) ch;
//    return ch;
//}
//#else
//
//
//
////重定向c库函数printf到串口，重定向后可使用printf函数
//
//int fputc(int ch,FILE *f)   //  函数默认的，在使用printf函数时自动调用
//{
//    /* 发送一个字节数据到串口 */
//    USART_SendData(USART1,(uint8_t) ch);
//    /* 等待发送完毕 */
//    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
//    return (ch);
//}
//#endif
///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
//{
//    /* 等待串口输入数据 */
//    while (USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
//
//    return (int)USART_ReceiveData(USART1);
//}
//
//#pragma import(__use_no_semihosting)
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#define GETCHAR_PROTOTYPE int __io_getchar(void)
//
//PUTCHAR_PROTOTYPE{
//    /* 发送一个字节数据到串口 */
//    USART_SendData(USART1,(uint8_t) ch);
//    /* 等待发送完毕 */
//    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
//    return (ch);
//}
//GETCHAR_PROTOTYPE{
//    /* 等待串口输入数据 */
//    while (USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
//
//    return (int)USART_ReceiveData(USART1);
//}
int __io_putchar(int ch)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}


void USART1_IRQHandler(void)
{

      extern uint8_t ucTemp ;

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {

        ucTemp = USART_ReceiveData( USART1 );
        USART_SendData(USART1,ucTemp);

        if(ucTemp == 2){
                LED2_ON;
            }else{
                LED2_OFF;
            }
        }
        //uart_receive=0;//蓝牙接收相关变量
        //uart_receive=USART_ReceiveData(USART1);
        //LED3_ON;
    }

