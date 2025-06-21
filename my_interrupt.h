#ifndef __MY_INTERRUPT_H__
#define __MY_INTERRUPT_H__

/**
 * @file    my_interrupt.h
 * @brief   中断及定时器初始化函数声明，适用于STC89C52等单片机
 */

/**
 * @brief  中断及定时器初始化函数
 * @note   配置定时器0、定时器2、外部中断1及中断优先级
 */
void Interrupt_Init(void);

#endif
