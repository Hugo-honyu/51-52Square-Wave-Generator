#include <REGX52.H> // STC89C52��Ƭ���Ĵ�������ͷ�ļ�
#include "OLED_show.h" // OLED��ʾ�����������
#include "OLED.h"      // OLED�ײ���������

// ===================== ȫ�ֱ������� =====================

uint8_t  Oled_line_num;        // ��ǰѡ�е��кţ�0~3��
uint8_t  Oled_host_flag;       // ������ˢ�±�־λ��1��ʾ��Ҫˢ��������
uint8_t  Oled_num_show_flag;   // ��ǰ�����ݸ��±�־λ��1��ʾ��Ҫˢ�µ�ǰ����ֵ
uint8_t  Oled_set_flag[4];     // ���ñ�־���飬0:δ���ã�1:����Ƶ�ʣ�2:����ռ�ձ�
uint16_t Oled_fre[4];          // ��ͨ����ǰƵ��ֵ
uint8_t  Oled_duty_cycle[4];   // ��ͨ����ǰռ�ձ�ֵ
char*    Oled_line[4];         // OLEDÿ����ʾ���ַ���ָ��

/**
 * @brief  OLED���������ʼ��������Ĭ��Ƶ�ʡ�ռ�ձȼ���ʾģ��
 * @note   ��ʼ����������ˢ�±�־λ��1��ѡ�е�0��
 */
void oled_show_init(void){
    Oled_line_num=0;       // Ĭ��ѡ�е�0��
    Oled_host_flag=1;      // ����������
    Oled_set_flag[0]=0;
    Oled_set_flag[1]=0;
    Oled_set_flag[2]=0;
    Oled_set_flag[3]=0;
    Oled_fre[0]=10;        // ��ͨ��Ĭ��Ƶ��
    Oled_fre[1]=20;
    Oled_fre[2]=30;
    Oled_fre[3]=40;
    Oled_duty_cycle[0]=10; // ��ͨ��Ĭ��ռ�ձ�
    Oled_duty_cycle[1]=20;
    Oled_duty_cycle[2]=30;
    Oled_duty_cycle[3]=40;
    Oled_line[0]="fre1:     HZ   %"; // ÿ����ʾģ��
    Oled_line[1]="fre2:     HZ   %";
    Oled_line[2]="fre3:     HZ   %";
    Oled_line[3]="fre4:     HZ   %";
}

/**
 * @brief  OLED��������ʾ������ˢ�������е�����
 * @note   ��ǰѡ���и�������ɫ����ʾ��������������ʾ
 */
void oled_show(void){
    uint8_t i=0;
    while(i<4){
        if(i==Oled_line_num){ // ��ǰѡ���и�����ʾ
            OLED_show_string(Line(i),Column(0),Oled_line[i],0); // ��ɫ��ʾ
            OLED_show_num(Line(i),Column(6),Oled_fre[i],3,0);   // Ƶ�ʷ�ɫ
            OLED_show_num(Line(i),Column(13),Oled_duty_cycle[i],2,0); // ռ�ձȷ�ɫ
        }else{ // ������������ʾ
            OLED_show_string(Line(i),0,Oled_line[i],1);    // ������ʾ
            OLED_show_num(Line(i),Column(6),Oled_fre[i],3,1);
            OLED_show_num(Line(i),Column(13),Oled_duty_cycle[i],2,1);
        }
        i++;
    }
}

/**
 * @brief  OLED��ǰѡ������ֵˢ�º�������ˢ�µ�ǰ�е�Ƶ�ʺ�ռ�ձ�
 */
void oled_num_show(void){
    OLED_show_num(Line(Oled_line_num),Column(6),Oled_fre[Oled_line_num],3,0); // ˢ��Ƶ��
    OLED_show_num(Line(Oled_line_num),Column(13),Oled_duty_cycle[Oled_line_num],2,0); // ˢ��ռ�ձ�
}