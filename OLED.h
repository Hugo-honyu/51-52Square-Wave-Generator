#ifndef __OLED_H__
#define __OLED_H__

// ===================== OLEDӲ�����Ŷ��� =====================
#define SCL P0_0   // OLED I2Cʱ���ߣ�SCL��
#define SDA P0_1   // OLED I2C�����ߣ�SDA��

// ===================== OLED��ʾ����� =====================
#define Line(x)   ((x)*2)   // �к�ת��Ϊҳ��ַ��ÿ��ռ2ҳ��
#define Column(x) ((x)*8)   // �к�ת��Ϊ���ص�ַ��ÿ�ַ�8���ؿ�

// ===================== OLED���ܺ������� =====================

/**
 * @brief  OLEDȫ��������ȫ�ף�
 */
void OLED_Clear_(void);

/**
 * @brief  OLED������ȫ�ڣ�
 */
void OLED_Clear(void);

/**
 * @brief  OLED��ʼ����������ʾ����
 */
void OLED_Init(void);

/**
 * @brief  OLED��ʾ�����ַ���8x16����
 * @param  Line   �кţ�ҳ��ַ��0~3��
 * @param  Column �кţ�0~15��
 * @param  Char   �ַ�
 * @param  mode   0:��ɫ��ʾ 1:������ʾ
 */
void OLED_show_char(uint8_t Line,uint8_t Column,char Char,uint8_t mode);

/**
 * @brief  OLED��ʾ�ַ���
 * @param  Line   �кţ�ҳ��ַ��0~3��
 * @param  Column �кţ�0~15��
 * @param  String �ַ���ָ��
 * @param  mode   0:��ɫ��ʾ 1:������ʾ
 */
void OLED_show_string(uint8_t Line,uint8_t Column,char *String,uint8_t mode);

/**
 * @brief  OLED��ʾ����
 * @param  Line   �кţ�ҳ��ַ��0~3��
 * @param  Column �кţ�0~15��
 * @param  num    Ҫ��ʾ������
 * @param  len    ��ʾ��λ��
 * @param  mode   0:��ɫ��ʾ 1:������ʾ
 */
void OLED_show_num(uint8_t Line,uint8_t Column,uint32_t num ,uint8_t len ,uint8_t mode);

#endif
