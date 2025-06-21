#ifndef __OLED_SHOW_H__
#define __OLED_SHOW_H__

#include "datatype.h" // 基本数据类型定义

// ===================== 全局变量声明 =====================

extern uint8_t Oled_line_num;      // 当前选中的行号（0~3）
extern uint8_t Oled_host_flag;     // 主界面刷新标志位，1表示需要刷新主界面
extern uint8_t Oled_num_show_flag; // 当前行数据更新标志位，1表示需要刷新当前行数值
extern uint8_t Oled_set_flag[4];   // 设置标志数组，0:未设置，1:设置频率，2:设置占空比
extern uint16_t Oled_fre[4];       // 各通道当前频率值
extern uint8_t Oled_duty_cycle[4]; // 各通道当前占空比值

// ===================== 函数声明 =====================

/**
 * @brief  OLED界面变量初始化，设置默认频率、占空比及显示模板
 */
void oled_show_init(void);

/**
 * @brief  OLED主界面显示函数，刷新所有行的内容
 */
void oled_show(void);

/**
 * @brief  OLED当前选中行数值刷新函数，仅刷新当前行的频率和占空比
 */
void oled_num_show(void);

#endif
