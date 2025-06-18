#include <REGX52.H>
#include "datatype.h"
#include "OLED_Font.h"
#include "OLED.h"
#include "datatype.h"

// 产生I2C起始信号
void OLED_I2C_Start(void)
{
    SDA = 1;
    SCL = 1;
    SDA = 0;
    SCL = 0;
}

// 产生I2C停止信号
void OLED_I2C_Stop(void)
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}

// 发送一个字节
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
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置低4位
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
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
  * @brief  OLED清屏~
  * @param  无
  * @retval 无
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
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
	
}

void OLED_show_char(uint8_t Line,uint8_t Column,char Char,uint8_t mode){

	uint8_t i = 0;
	uint8_t chr = Char-' ';
	
	OLED_SetCursor(Line,Column);	//设置光标
	if(mode){
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(OLED_F8x16[chr][i]);			//显示上半部分内容
		}
		OLED_SetCursor(Line+1,Column);	//设置光标位置在下半部分
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(OLED_F8x16[chr][i + 8]);		//显示下半部分内容
		}
	}else{
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(~OLED_F8x16[chr][i]);			//显示上半部分内容
		}
		OLED_SetCursor(Line+1,Column);	//设置光标位置在下半部分
		for (i = 0; i < 8; i++)
		{
			OLED_WriteData(~OLED_F8x16[chr][i + 8]);		//显示下半部分内容
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

//x底	y指数
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

//// 放到文件顶部，全局变量区域
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
//	OLED_SetCursor(Line,Column);	//设置光标
//	while(j<=Buf_Num){
//		OLED_WriteData(Buf_H[j]);
//		j++;
//	}
//	j=0;
//	OLED_SetCursor(Line+1,Column);	//设置光标
//	while(j<=Buf_Num){
//		OLED_WriteData(Buf_L[j]);
//		j++;
//	}
//}
