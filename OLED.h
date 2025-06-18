#ifndef __OLED_H__
#define __OLED_H__


#define SCL P0_0
#define SDA P0_1

#define Line(x)		(x*2)
#define Column(x)	(x*8)

void OLED_Clear_(void);
void OLED_Clear(void);

void OLED_Init(void);

void OLED_show_logo(void);

void OLED_show_char(uint8_t Line,uint8_t Column,char Char,uint8_t mode);
void OLED_show_string(uint8_t Line,uint8_t Column,char *String,uint8_t mode);
void OLED_show_num(uint8_t Line,uint8_t Column,uint32_t num ,uint8_t len ,uint8_t mode);

#endif
