#include <REGX52.H>
#include "datatype.h"
#include "OLED_Font.h"
#include "OLED.h"
#include "datatype.h"

// ����I2C��ʼ�ź�
void OLED_I2C_Start(void)
{
    SDA = 1;
    SCL = 1;
    SDA = 0;
    SCL = 0;
}

// ����I2Cֹͣ�ź�
void OLED_I2C_Stop(void)
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}

// ����һ���ֽ�
void OLED_I2C_SendByte(unsigned char dat)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SDA = (dat & 0x80) ? 1 : 0;
        SCL = 1;
        SCL = 0;
        dat <<= 1;
    }
	SCL = 1;
    SCL = 0;
}

/**
  * @brief  OLEDд����
  * @param  Command Ҫд�������
  * @retval ��
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//�ӻ���ַ
	OLED_I2C_SendByte(0x00);		//д����
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLEDд����
  * @param  Data Ҫд�������
  * @retval ��
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//�ӻ���ַ
	OLED_I2C_SendByte(0x40);		//д����
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED���ù��λ��
  * @param  Y �����Ͻ�Ϊԭ�㣬���·�������꣬��Χ��0~7
  * @param  X �����Ͻ�Ϊԭ�㣬���ҷ�������꣬��Χ��0~127
  * @retval ��
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//����Yλ��
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//����Xλ�ø�4λ
	OLED_WriteCommand(0x00 | (X & 0x0F));			//����Xλ�õ�4λ
}

/**
  * @brief  OLED����
  * @param  ��
  * @retval ��
  */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}


/**
  * @brief  OLED����~
  * @param  ��
  * @retval ��
  */
void OLED_Clear_(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0xFF);
		}
	}
}

//void OLED_show_logo(void){
//	uint8_t i, j;
//	for (j = 0; j < 8; j++)
//	{
//		OLED_SetCursor(j, 0);
//		for(i = 0; i < 128; i++)
//		{
//			OLED_WriteData(windows_logo_bitmap[j*128+i]);
//		}
//	}
//}

void OLED_Init(void)
{
	SDA=1;
	SCL=1;
	
	OLED_WriteCommand(0xAE);	//�ر���ʾ
	
	OLED_WriteCommand(0xD5);	//������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//���ö�·������
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//������ʾƫ��
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//������ʾ��ʼ��
	
	OLED_WriteCommand(0xA1);	//�������ҷ���0xA1���� 0xA0���ҷ���
	
	OLED_WriteCommand(0xC8);	//�������·���0xC8���� 0xC0���·���

	OLED_WriteCommand(0xDA);	//����COM����Ӳ������
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//���öԱȶȿ���
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//����Ԥ�������
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//����VCOMHȡ��ѡ�񼶱�
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//����������ʾ��/�ر�

	OLED_WriteCommand(0xA6);	//��������/��ת��ʾ

	OLED_WriteCommand(0x8D);	//���ó���
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//������ʾ
	
}

void OLED_show_char(uint8_t Line,uint8_t Column,char Char,uint8_t mode){

	uint8_t i = 0;
	uint8_t chr = Char-' ';
	
	OLED_SetCursor(Line,Column);	//���ù��
	if(mode){
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(OLED_F8x16[chr][i]);			//��ʾ�ϰ벿������
		}
		OLED_SetCursor(Line+1,Column);	//���ù��λ�����°벿��
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(OLED_F8x16[chr][i + 8]);		//��ʾ�°벿������
		}
	}else{
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(~OLED_F8x16[chr][i]);			//��ʾ�ϰ벿������
		}
		OLED_SetCursor(Line+1,Column);	//���ù��λ�����°벿��
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(~OLED_F8x16[chr][i + 8]);		//��ʾ�°벿������
		}
	}

}

void OLED_show_string(uint8_t Line,uint8_t Column,char *String,uint8_t mode){
	uint8_t i=0;
	EA = 0;

	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_show_char(Line, Column + i*8, String[i],mode);
	}
	EA = 1;
}

//x��	yָ��
uint32_t Pow(uint16_t x,uint16_t y){
	uint32_t num=1;
	while(y--){
		num*=x;
	}
	return num;
}

void OLED_show_num(uint8_t Line,uint8_t Column,uint32_t num ,uint8_t len ,uint8_t mode){
	
	uint8_t i=0;
	uint8_t chr;
	EA=0;
	for(i = 0; i<len; i++){
		chr=num/Pow(10,len-1-i)%10 + '0';
		OLED_show_char(Line, Column + i*8, chr ,mode);
	}
	EA=1;
}

//// �ŵ��ļ�������ȫ�ֱ�������
//uint8_t Buf_H[128];
//uint8_t Buf_L[128];

//void OLED_show_string(uint8_t Line,uint8_t Column,char *String,uint8_t mode){
//	uint8_t i = 0 , j = 0 ;
//	uint8_t chr;

//	uint8_t Buf_Num=0;
//	if(mode){
//		while(String[i]='\0'){
//			chr= String[i]-' ';
//			while(j<8){
//				Buf_H[Buf_Num]=OLED_F8x16[chr][j];
//				Buf_L[Buf_Num]=OLED_F8x16[chr][j + 8];
//				j++;
//			}
//			j=0;
//			Buf_Num++;
//			i++;
//		}	
//	}else{
//		while(String[i]='\0'){
//			chr= String[i]-' ';
//			while(j<8){
//				Buf_H[Buf_Num]=~OLED_F8x16[chr][j];
//				Buf_L[Buf_Num]=~OLED_F8x16[chr][j + 8];
//				j++;
//			}
//			j=0;
//			Buf_Num++;
//			i++;
//		}
//	}

//	
//	OLED_SetCursor(Line,Column);	//���ù��
//	while(j<=Buf_Num){
//		OLED_WriteData(Buf_H[j]);
//		j++;
//	}
//	j=0;
//	OLED_SetCursor(Line+1,Column);	//���ù��
//	while(j<=Buf_Num){
//		OLED_WriteData(Buf_L[j]);
//		j++;
//	}
//}
