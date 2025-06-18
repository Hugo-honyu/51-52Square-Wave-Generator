#include <REGX52.H>
#include "datatype.h"
#include "Delay.h"
#include "OLED.h"
#include "my_interrupt.h"
#include "OLED_show.h"

//Timer2采样率
#define Timer2_HZ  5000.0

uint8_t start_flag=0;

void main(){
	
	//初始化
	OLED_Init();
	OLED_Clear_();
	OLED_Clear();

	oled_show_init();
	
	Interrupt_Init();
	while(1){
		if(Oled_num_show_flag){
			Oled_num_show_flag=0;
			oled_num_show();
		}
		if(Oled_host_flag){
			oled_show();
			Oled_host_flag=0;
		}		
	}
}


void INT1_ISR() interrupt 2 {
	bit key1=1,key1_last=1;
	Delay(20);
	key1=0;
	while(P3_3==0);
	Delay(20);
	IE1=0;				//防止再次进中断
	
	if( key1==0 && key1_last==1 ){
		//key1按下逻辑,进入设置界面\设置频率\占空比
		Oled_set_flag[Oled_line_num]++;
		Oled_set_flag[Oled_line_num]%=3;
		//KEY4响应不了中断时的紧急处理手段，增强系统鲁棒性
		TR2=0;
		Oled_host_flag=1;	
	}
	key1_last=key1;
}

//10ms
void Timer0_ISR(void) interrupt 1{
	static uint8_t KeyTick=0;
	static uint8_t key2=1,key3=1,key4=1;
	static uint8_t key2_last=1,key3_last=1,key4_last=1;
	static uint8_t time_num;
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xB8;		//设置定时初值	
	
	KeyTick++;
	
	if(KeyTick==1){	//按键key2~4判定
		KeyTick=0;
		
		key2=P3_4;
		key3=P3_6;
		key4=P3_7;
		if(key2==0&&key2_last==1){//key2按下，加操作
			if(Oled_set_flag[Oled_line_num]==1){
				Oled_fre[Oled_line_num]++;
			}
			else if(Oled_set_flag[Oled_line_num]==2){
				Oled_duty_cycle[Oled_line_num]++;
				if(Oled_duty_cycle[Oled_line_num]>100){
				Oled_duty_cycle[Oled_line_num]=0;
				}
			}
			else{
				Oled_line_num++;
				if(Oled_line_num>3){Oled_line_num=0;}			
			}				
		}
		if(key3==0&&key3_last==1){//key3按下，减操作
			if(Oled_set_flag[Oled_line_num]==1){
				Oled_fre[Oled_line_num]--;
			}
			else if(Oled_set_flag[Oled_line_num]==2){
				Oled_duty_cycle[Oled_line_num]--;
				if(Oled_duty_cycle[Oled_line_num]>100){
				Oled_duty_cycle[Oled_line_num]=100;
				}
			}
			else{
				Oled_line_num--;
				if(Oled_line_num>3){Oled_line_num=3;}			
			}	
		}
		if(key4==0&&key4_last==1){
			TR2=~TR2;
			if(TR2==0){
				P1=0xff;
				//重新进入设置阶段，清除Oled_set_flag
				Oled_set_flag[0]=0;
				Oled_set_flag[1]=0;
				Oled_set_flag[2]=0;
				Oled_set_flag[3]=0;
			}else{
				start_flag=1;
			}
		}//key4按下	打开频率输出
		//长按判定 2s time_num=100;
		if(key2==0&&key2_last==0){
			time_num++;
			if(time_num>100){
				if(Oled_set_flag[Oled_line_num]==1){
					Oled_fre[Oled_line_num]++;
				}
				else if(Oled_set_flag[Oled_line_num]==2){
					Oled_duty_cycle[Oled_line_num]++;	
					if(Oled_duty_cycle[Oled_line_num]>100){
					Oled_duty_cycle[Oled_line_num]=0;
					}
				}
				Oled_num_show_flag=1;
			}
		}
		if(key3==0&&key3_last==0){
			time_num++;
			if(time_num>100){
				if(Oled_set_flag[Oled_line_num]==1){
					Oled_fre[Oled_line_num]--;
				}
				else if(Oled_set_flag[Oled_line_num]==2){
					Oled_duty_cycle[Oled_line_num]--;	
					if(Oled_duty_cycle[Oled_line_num]>100){
					Oled_duty_cycle[Oled_line_num]=100;
					}
				}
				Oled_num_show_flag=1;
			}
		}
		//松手判定
		if(key2==1&&key2_last==0){
			time_num=0;
			Oled_host_flag=1;
		}
		if(key3==1&&key3_last==0){
			time_num=0;
			Oled_host_flag=1;
		}
		key2_last=key2;
		key3_last=key3;
		key4_last=key4;
	}

}

//void set_fre(uint8_t x, bit value) {
//    switch (x) {
//        case 0: P2_0 = value; break;
//        case 1: P2_1 = value; break;
//        case 2: P2_2 = value; break;
//        case 3: P2_3 = value; break;
//    }
//}


void Timer2_ISR() interrupt 5 {
	static uint16_t fre_num[4];
	static uint16_t _fre_num[4];
	static uint16_t _duty_cycle_num[4];
	uint8_t i=0;
	P1=~P1;
	if(TF2){
		TF2 = 0;            // 必须手动清除中断标志
		if(start_flag){
			start_flag=0;
			for(i=0;i<4;i++){
				_fre_num[i]=Timer2_HZ/Oled_fre[i];
				_duty_cycle_num[i]=Timer2_HZ*Oled_duty_cycle[i]/Oled_fre[i]/100;
			}
		}
		// ===== fre判断 =====
		for(i=0;i<4;i++){
			fre_num[i]++;	
			if(fre_num[i] >= _fre_num[i]) fre_num[i] = 0;
			if(fre_num[i] < _duty_cycle_num[i])
				switch (i) {
				case 0: P2_0 = 1; break;
				case 1: P2_1 = 1; break;
				case 2: P2_2 = 1; break;
				case 3: P2_3 = 1; break;
				}
			else
				switch (i) {
				case 0: P2_0 = 0; break;
				case 1: P2_1 = 0; break;
				case 2: P2_2 = 0; break;
				case 3: P2_3 = 0; break;
				}	
		}	
	}

}
