#ifndef __DELAY_H__
#define __DELAY_H__

/**
 * @file    Delay.h
 * @brief   软件延时函数声明，适用于STC89C52等单片机
 */

/**
 * @brief  毫秒级延时函数（阻塞式）
 * @param  xms 延时时间，单位：毫秒
 */
void Delay(unsigned int xms);

#endif
