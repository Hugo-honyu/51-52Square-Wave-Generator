#include <REGX52.H>
#include "OLED_show.h"
#include "OLED.h"

uint8_t 	Oled_line_num;				//当前选中的行数
uint8_t 	Oled_host_flag;				//主界面显示标志位
uint8_t 	Oled_num_show_flag;			//当前行数据更新标志位
uint8_t 	Oled_set_flag[4];			// 设置标志位  0:没有设置，1:设置频率，2:设置占空比
uint16_t 	Oled_fre[4];				//当前频率
uint8_t 	Oled_duty_cycle[4];			//占空比
char* 		Oled_line[4];

void oled_show_init(void){
	Oled_line_num=0;
	Oled_host_flag=1;
	Oled_set_flag[0]=0;
	Oled_set_flag[1]=0;
	Oled_set_flag[2]=0;
	Oled_set_flag[3]=0;
	Oled_fre[0]=10;
	Oled_fre[1]=20;
	Oled_fre[2]=30;
	Oled_fre[3]=40;
	Oled_duty_cycle[0]=10;
	Oled_duty_cycle[1]=20;
	Oled_duty_cycle[2]=30;
	Oled_duty_cycle[3]=40;
	Oled_line[0]="fre1:     HZ   %";
	Oled_line[1]="fre2:     HZ   %";
	Oled_line[2]="fre3:     HZ   %";
	Oled_line[3]="fre4:     HZ   %";
}

void oled_show(void){
	uint8_t i=0;

	while(i<4){
		if(i==Oled_line_num){
			OLED_show_string(Line(i),Column(0),Oled_line[i],0);
			OLED_show_num(Line(i),Column(6),Oled_fre[i],3,0);
			OLED_show_num(Line(i),Column(13),Oled_duty_cycle[i],2,0);
		}else{
			OLED_show_string(Line(i),0,Oled_line[i],1);	
			OLED_show_num(Line(i),Column(6),Oled_fre[i],3,1);
			OLED_show_num(Line(i),Column(13),Oled_duty_cycle[i],2,1);
		}
		i++;
	}

}

void oled_num_show(void){
	OLED_show_num(Line(Oled_line_num),Column(6),Oled_fre[Oled_line_num],3,0);
	OLED_show_num(Line(Oled_line_num),Column(13),Oled_duty_cycle[Oled_line_num],2,0);
}