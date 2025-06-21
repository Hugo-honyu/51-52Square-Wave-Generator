#include <REGX52.H> // STC89C52��Ƭ���Ĵ�������ͷ�ļ�
#include "datatype.h" // �������Ͷ���
#include "Delay.h"    // ��ʱ��������
#include "OLED.h"     // OLED��ʾ��غ�������
#include "my_interrupt.h" // �жϳ�ʼ����������
#include "OLED_show.h"    // OLED��ʾ������غ�������

uint8_t start_flag=0; // ������־λ

void main(){
	// ��ʼ��OLED��ʾ
	OLED_Init();
	OLED_Clear_(); // ȫ������
	OLED_Clear();  // ����

	oled_show_init(); // OLED���������ʼ��
	
	Interrupt_Init(); // ��ʼ����ʱ�����ж�
	while(1){
		if(Oled_num_show_flag){ // ��ֵ���±�־
			Oled_num_show_flag=0;
			oled_num_show(); // ˢ�µ�ǰ����ֵ
		}
		if(Oled_host_flag){ // ������ˢ�±�־
			oled_show(); // ˢ��������
			Oled_host_flag=0;
		}		
	}
}

// �ⲿ�ж�1������������1����
void INT1_ISR() interrupt 2 {
	bit key1=1,key1_last=1;
	Delay(20); // ����
	key1=0;
	while(P3_3==0); // �ȴ������ɿ�
	Delay(20); // ����
	IE1=0; // ��ֹ�ٴν��ж�
	
	if( key1==0 && key1_last==1 ){
		// key1�����߼�,�������ý��� ����Ƶ�ʺ�ռ�ձ�
		Oled_set_flag[Oled_line_num]++;
		Oled_set_flag[Oled_line_num]%=3;
		TR2=0; // �ر�Ƶ�����
		Oled_host_flag=1; // ˢ��������
	}
	key1_last=key1;
}

// ��ʱ��0�жϷ�������10ms���ڣ�������2/3/4
void Timer0_ISR(void) interrupt 1{
	static uint8_t KeyTick=0;
	static uint8_t key2=1,key3=1,key4=1;
	static uint8_t key2_last=1,key3_last=1,key4_last=1;
	static uint8_t time_num;
	TL0 = 0x00; // ���ö�ʱ��ֵ
	TH0 = 0xB8; // ���ö�ʱ��ֵ	
	
    TF2 = 0; // �ֶ���������־
	
	KeyTick++;
	
	if(KeyTick==1){ // ����key2~4�ж�
		KeyTick=0;
		
		key2=P3_4; // ��ȡ����2
		key3=P3_6; // ��ȡ����3
		key4=P3_7; // ��ȡ����4
		if(key2==0&&key2_last==1){ // key2����
			if(Oled_set_flag[Oled_line_num]==1){
				Oled_fre[Oled_line_num]++; // Ƶ��+
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
		if(key3==0&&key3_last==1){ // key3����
			if(Oled_set_flag[Oled_line_num]==1){
				Oled_fre[Oled_line_num]--; // Ƶ��-
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
		if(key4==0&&key4_last==1){ // key4����
			TR2=~TR2; // Ƶ���������
			if(TR2==0){
				P1=0xff;
				// ���½������ý׶Σ����Oled_set_flag
				Oled_set_flag[0]=0;
				Oled_set_flag[1]=0;
				Oled_set_flag[2]=0;
				Oled_set_flag[3]=0;
			}else{
				start_flag=1;
			}
		}//key4���� ��Ƶ�����
		// �����ж� 2s time_num=100;
		if(key2==0&&key2_last==0){
			time_num++;
			if(time_num>100){
				if(Oled_set_flag[Oled_line_num]==1){
					Oled_fre[Oled_line_num]++; // ����Ƶ��+
				}
				else if(Oled_set_flag[Oled_line_num]==2){
					Oled_duty_cycle[Oled_line_num]++;	
					if(Oled_duty_cycle[Oled_line_num]>100){
					Oled_duty_cycle[Oled_line_num]=0;
					}
				}
				Oled_num_show_flag=1; // ˢ����ֵ
			}
		}
		if(key3==0&&key3_last==0){
			time_num++;
			if(time_num>100){
				if(Oled_set_flag[Oled_line_num]==1){
					Oled_fre[Oled_line_num]--; // ����Ƶ��-
				}
				else if(Oled_set_flag[Oled_line_num]==2){
					Oled_duty_cycle[Oled_line_num]--;	
					if(Oled_duty_cycle[Oled_line_num]>100){
					Oled_duty_cycle[Oled_line_num]=100;
					}
				}
				Oled_num_show_flag=1; // ˢ����ֵ
			}
		}
		// �����ж�
		if(key2==1&&key2_last==0){
			time_num=0;
			Oled_host_flag=1; // ˢ��������
		}
		if(key3==1&&key3_last==0){
			time_num=0;
			Oled_host_flag=1; // ˢ��������
		}
		key2_last=key2;
		key3_last=key3;
		key4_last=key4;
	}

}

// ����Ƶ������˿ڵ�ƽ
void set_fre(uint8_t x, bit value) {
    switch (x) {
        case 0: P2_0 = value; break;
        case 1: P2_1 = value; break;
        case 2: P2_2 = value; break;
        case 3: P2_3 = value; break;
    }
}

// ��ʱ��2�жϷ�������0.25ms������Ƶ��/ռ�ձ����
void Timer2_ISR() interrupt 5 {
	static uint16_t fre_num[4]; // ������
	static uint16_t _fre_num[4]; // Ƶ�����ڼ���
	static uint16_t _duty_cycle_num[4]; // ռ�ձȼ���
	uint8_t i=0;
	P1=~P1; // ָʾ�Ʒ�ת
	if(TF2){
		TF2 = 0; // �����ֶ�����жϱ�־
		if(start_flag){
			start_flag=0;
			for(i=0;i<4;i++){
				_fre_num[i]=4000/Oled_fre[i]; // ��������
				_duty_cycle_num[i]=40*Oled_duty_cycle[i]/Oled_fre[i]; // ����ռ�ձ�
			}
		}
		// ===== fre1~fre4��� =====
		for(i=0;i<4;i++){
			fre_num[i]++; 	// ����
			if(fre_num[i] >= _fre_num[i]) fre_num[i] = 0; // �����ڹ���
			if(fre_num[i] < _duty_cycle_num[i])
				set_fre(i,1); // ����ߵ�ƽ
			else
				set_fre(i,0); // ����͵�ƽ
		}
	}
}
