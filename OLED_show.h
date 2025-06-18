#ifndef __OLED_SHOW_H__
#define __OLED_SHOW_H__
#include "datatype.h"

extern uint8_t Oled_line_num;				//当前选中的行数
extern uint8_t Oled_host_flag;				//主界面显示标志位
extern uint8_t Oled_num_show_flag;			//当前行数据更新标志位
extern uint8_t Oled_set_flag[4];			// 设置标志位 0:没有设置，1:设置频率，2:设置占空比
extern uint16_t Oled_fre[4];				//当前频率
extern uint8_t Oled_duty_cycle[4];			//占空比


void oled_show_init(void);
void oled_show(void);
void oled_num_show(void);

#endif
