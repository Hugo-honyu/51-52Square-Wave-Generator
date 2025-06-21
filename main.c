#include <REGX52.H> // STC89C52单片机寄存器定义头文件
#include "datatype.h" // 数据类型定义
#include "Delay.h"    // 延时函数声明
#include "OLED.h"     // OLED显示相关函数声明
#include "my_interrupt.h" // 中断初始化函数声明
#include "OLED_show.h"    // OLED显示界面相关函数声明

uint8_t start_flag=0; // 启动标志位

void main(){
	// 初始化OLED显示
	OLED_Init();
	OLED_Clear_(); // 全屏点亮
	OLED_Clear();  // 清屏

	oled_show_init(); // OLED界面变量初始化
	
	Interrupt_Init(); // 初始化定时器和中断
	while(1){
		if(Oled_num_show_flag){ // 数值更新标志
			Oled_num_show_flag=0;
			oled_num_show(); // 刷新当前行数值
		}
		if(Oled_host_flag){ // 主界面刷新标志
			oled_show(); // 刷新主界面
			Oled_host_flag=0;
		}		
	}
}

// 外部中断1服务函数，按键1处理
void INT1_ISR() interrupt 2 {
	bit key1=1,key1_last=1;
	Delay(20); // 消抖
	key1=0;
	while(P3_3==0); // 等待按键松开
	Delay(20); // 消抖
	IE1=0; // 防止再次进中断
	
	if( key1==0 && key1_last==1 ){
		// key1按下逻辑,进入设置界面 设置频率和占空比
		Oled_set_flag[Oled_line_num]++;
		Oled_set_flag[Oled_line_num]%=3;
		TR2=0; // 关闭频率输出
		Oled_host_flag=1; // 刷新主界面
	}
	key1_last=key1;
}

// 定时器0中断服务函数，10ms周期，处理按键2/3/4
void Timer0_ISR(void) interrupt 1{
	static uint8_t KeyTick=0;
	static uint8_t key2=1,key3=1,key4=1;
	static uint8_t key2_last=1,key3_last=1,key4_last=1;
	static uint8_t time_num;
	TL0 = 0x00; // 设置定时初值
	TH0 = 0xB8; // 设置定时初值	
	
    TF2 = 0; // 手动清除溢出标志
	
	KeyTick++;
	
	if(KeyTick==1){ // 按键key2~4判定
		KeyTick=0;
		
		key2=P3_4; // 读取按键2
		key3=P3_6; // 读取按键3
		key4=P3_7; // 读取按键4
		if(key2==0&&key2_last==1){ // key2按下
			if(Oled_set_flag[Oled_line_num]==1){
				Oled_fre[Oled_line_num]++; // 频率+
			}
			else if(Oled_set_flag[Oled_line_num]==2){
				Oled_duty_cycle[Oled_line_num]++;
				if(Oled_duty_cycle[Oled_line_num]>100){
				Oled_duty_cycle[Oled_line_num]=0;
				}
			}else{
				Oled_line_num++;
				if(Oled_line_num>3){Oled_line_num=0;}			
			}				
		}
		if(key3==0&&key3_last==1){ // key3按下
			if(Oled_set_flag[Oled_line_num]==1){
				Oled_fre[Oled_line_num]--; // 频率-
			}
			else if(Oled_set_flag[Oled_line_num]==2){
				Oled_duty_cycle[Oled_line_num]--;
				if(Oled_duty_cycle[Oled_line_num]>100){
				Oled_duty_cycle[Oled_line_num]=100;
				}
			}else{
				Oled_line_num--;
				if(Oled_line_num>3){Oled_line_num=3;}			
			}	
		}
		if(key4==0&&key4_last==1){ // key4按下
			TR2=~TR2; // 频率输出开关
			if(TR2==0){
				P1=0xff;
				// 重新进入设置阶段，清除Oled_set_flag
				Oled_set_flag[0]=0;
				Oled_set_flag[1]=0;
				Oled_set_flag[2]=0;
				Oled_set_flag[3]=0;
			}else{
				start_flag=1;
			}
		}//key4按下 打开频率输出
		// 长按判定 2s time_num=100;
		if(key2==0&&key2_last==0){
			time_num++;
			if(time_num>100){
				if(Oled_set_flag[Oled_line_num]==1){
					Oled_fre[Oled_line_num]++; // 长按频率+
				}
				else if(Oled_set_flag[Oled_line_num]==2){
					Oled_duty_cycle[Oled_line_num]++;	
					if(Oled_duty_cycle[Oled_line_num]>100){
					Oled_duty_cycle[Oled_line_num]=0;
					}
				}
				Oled_num_show_flag=1; // 刷新数值
			}
		}
		if(key3==0&&key3_last==0){
			time_num++;
			if(time_num>100){
				if(Oled_set_flag[Oled_line_num]==1){
					Oled_fre[Oled_line_num]--; // 长按频率-
				}
				else if(Oled_set_flag[Oled_line_num]==2){
					Oled_duty_cycle[Oled_line_num]--;	
					if(Oled_duty_cycle[Oled_line_num]>100){
					Oled_duty_cycle[Oled_line_num]=100;
					}
				}
				Oled_num_show_flag=1; // 刷新数值
			}
		}
		// 松手判定
		if(key2==1&&key2_last==0){
			time_num=0;
			Oled_host_flag=1; // 刷新主界面
		}
		if(key3==1&&key3_last==0){
			time_num=0;
			Oled_host_flag=1; // 刷新主界面
		}
		key2_last=key2;
		key3_last=key3;
		key4_last=key4;
	}

}

// 设置频率输出端口电平
void set_fre(uint8_t x, bit value) {
    switch (x) {
        case 0: P2_0 = value; break;
        case 1: P2_1 = value; break;
        case 2: P2_2 = value; break;
        case 3: P2_3 = value; break;
    }
}

// 定时器2中断服务函数，0.25ms采样，频率/占空比输出
void Timer2_ISR() interrupt 5 {
	static uint16_t fre_num[4]; // 计数器
	static uint16_t _fre_num[4]; // 频率周期计数
	static uint16_t _duty_cycle_num[4]; // 占空比计数
	uint8_t i=0;
	P1=~P1; // 指示灯翻转
	if(TF2){
		TF2 = 0; // 必须手动清除中断标志
		if(start_flag){
			start_flag=0;
			for(i=0;i<4;i++){
				_fre_num[i]=4000/Oled_fre[i]; // 计算周期
				_duty_cycle_num[i]=40*Oled_duty_cycle[i]/Oled_fre[i]; // 计算占空比
			}
		}
		// ===== fre1~fre4输出 =====
		for(i=0;i<4;i++){
			fre_num[i]++; 	// 计数
			if(fre_num[i] >= _fre_num[i]) fre_num[i] = 0; // 到周期归零
			if(fre_num[i] < _duty_cycle_num[i])
				set_fre(i,1); // 输出高电平
			else
				set_fre(i,0); // 输出低电平
		}
	}
}
