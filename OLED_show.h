#ifndef __OLED_SHOW_H__
#define __OLED_SHOW_H__

#include "datatype.h" // �����������Ͷ���

// ===================== ȫ�ֱ������� =====================

extern uint8_t Oled_line_num;      // ��ǰѡ�е��кţ�0~3��
extern uint8_t Oled_host_flag;     // ������ˢ�±�־λ��1��ʾ��Ҫˢ��������
extern uint8_t Oled_num_show_flag; // ��ǰ�����ݸ��±�־λ��1��ʾ��Ҫˢ�µ�ǰ����ֵ
extern uint8_t Oled_set_flag[4];   // ���ñ�־���飬0:δ���ã�1:����Ƶ�ʣ�2:����ռ�ձ�
extern uint16_t Oled_fre[4];       // ��ͨ����ǰƵ��ֵ
extern uint8_t Oled_duty_cycle[4]; // ��ͨ����ǰռ�ձ�ֵ

// ===================== �������� =====================

/**
 * @brief  OLED���������ʼ��������Ĭ��Ƶ�ʡ�ռ�ձȼ���ʾģ��
 */
void oled_show_init(void);

/**
 * @brief  OLED��������ʾ������ˢ�������е�����
 */
void oled_show(void);

/**
 * @brief  OLED��ǰѡ������ֵˢ�º�������ˢ�µ�ǰ�е�Ƶ�ʺ�ռ�ձ�
 */
void oled_num_show(void);

#endif
