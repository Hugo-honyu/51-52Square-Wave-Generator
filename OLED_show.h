#ifndef __OLED_SHOW_H__
#define __OLED_SHOW_H__
#include "datatype.h"

extern uint8_t Oled_line_num;				//��ǰѡ�е�����
extern uint8_t Oled_host_flag;				//��������ʾ��־λ
extern uint8_t Oled_num_show_flag;			//��ǰ�����ݸ��±�־λ
extern uint8_t Oled_set_flag[4];			// ���ñ�־λ 0:û�����ã�1:����Ƶ�ʣ�2:����ռ�ձ�
extern uint16_t Oled_fre[4];				//��ǰƵ��
extern uint8_t Oled_duty_cycle[4];			//ռ�ձ�


void oled_show_init(void);
void oled_show(void);
void oled_num_show(void);

#endif
