#include <REGX52.H> // STC89C52单片机寄存器定义头文件
#include "OLED_show.h" // OLED显示界面相关声明
#include "OLED.h"      // OLED底层驱动声明

// ===================== 全局变量定义 =====================

uint8_t  Oled_line_num;        // 当前选中的行号（0~3）
uint8_t  Oled_host_flag;       // 主界面刷新标志位，1表示需要刷新主界面
uint8_t  Oled_num_show_flag;   // 当前行数据更新标志位，1表示需要刷新当前行数值
uint8_t  Oled_set_flag[4];     // 设置标志数组，0:未设置，1:设置频率，2:设置占空比
uint16_t Oled_fre[4];          // 各通道当前频率值
uint8_t  Oled_duty_cycle[4];   // 各通道当前占空比值
char*    Oled_line[4];         // OLED每行显示的字符串指针

/**
 * @brief  OLED界面变量初始化，设置默认频率、占空比及显示模板
 * @note   初始化后，主界面刷新标志位置1，选中第0行
 */
void oled_show_init(void){
    Oled_line_num=0;       // 默认选中第0行
    Oled_host_flag=1;      // 进入主界面
    Oled_set_flag[0]=0;
    Oled_set_flag[1]=0;
    Oled_set_flag[2]=0;
    Oled_set_flag[3]=0;
    Oled_fre[0]=10;        // 各通道默认频率
    Oled_fre[1]=20;
    Oled_fre[2]=30;
    Oled_fre[3]=40;
    Oled_duty_cycle[0]=10; // 各通道默认占空比
    Oled_duty_cycle[1]=20;
    Oled_duty_cycle[2]=30;
    Oled_duty_cycle[3]=40;
    Oled_line[0]="fre1:     HZ   %"; // 每行显示模板
    Oled_line[1]="fre2:     HZ   %";
    Oled_line[2]="fre3:     HZ   %";
    Oled_line[3]="fre4:     HZ   %";
}

/**
 * @brief  OLED主界面显示函数，刷新所有行的内容
 * @note   当前选中行高亮（反色）显示，其他行正常显示
 */
void oled_show(void){
    uint8_t i=0;
    while(i<4){
        if(i==Oled_line_num){ // 当前选中行高亮显示
            OLED_show_string(Line(i),Column(0),Oled_line[i],0); // 反色显示
            OLED_show_num(Line(i),Column(6),Oled_fre[i],3,0);   // 频率反色
            OLED_show_num(Line(i),Column(13),Oled_duty_cycle[i],2,0); // 占空比反色
        }else{ // 其他行正常显示
            OLED_show_string(Line(i),0,Oled_line[i],1);    // 正常显示
            OLED_show_num(Line(i),Column(6),Oled_fre[i],3,1);
            OLED_show_num(Line(i),Column(13),Oled_duty_cycle[i],2,1);
        }
        i++;
    }
}

/**
 * @brief  OLED当前选中行数值刷新函数，仅刷新当前行的频率和占空比
 */
void oled_num_show(void){
    OLED_show_num(Line(Oled_line_num),Column(6),Oled_fre[Oled_line_num],3,0); // 刷新频率
    OLED_show_num(Line(Oled_line_num),Column(13),Oled_duty_cycle[Oled_line_num],2,0); // 刷新占空比
}