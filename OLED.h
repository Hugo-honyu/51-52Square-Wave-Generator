#ifndef __OLED_H__
#define __OLED_H__

// ===================== OLED硬件引脚定义 =====================
#define SCL P0_0   // OLED I2C时钟线（SCL）
#define SDA P0_1   // OLED I2C数据线（SDA）

// ===================== OLED显示坐标宏 =====================
#define Line(x)   ((x)*2)   // 行号转换为页地址（每行占2页）
#define Column(x) ((x)*8)   // 列号转换为像素地址（每字符8像素宽）

// ===================== OLED功能函数声明 =====================

/**
 * @brief  OLED全屏点亮（全白）
 */
void OLED_Clear_(void);

/**
 * @brief  OLED清屏（全黑）
 */
void OLED_Clear(void);

/**
 * @brief  OLED初始化，配置显示参数
 */
void OLED_Init(void);

/**
 * @brief  OLED显示单个字符（8x16点阵）
 * @param  Line   行号（页地址，0~3）
 * @param  Column 列号（0~15）
 * @param  Char   字符
 * @param  mode   0:反色显示 1:正常显示
 */
void OLED_show_char(uint8_t Line,uint8_t Column,char Char,uint8_t mode);

/**
 * @brief  OLED显示字符串
 * @param  Line   行号（页地址，0~3）
 * @param  Column 列号（0~15）
 * @param  String 字符串指针
 * @param  mode   0:反色显示 1:正常显示
 */
void OLED_show_string(uint8_t Line,uint8_t Column,char *String,uint8_t mode);

/**
 * @brief  OLED显示数字
 * @param  Line   行号（页地址，0~3）
 * @param  Column 列号（0~15）
 * @param  num    要显示的数字
 * @param  len    显示的位数
 * @param  mode   0:反色显示 1:正常显示
 */
void OLED_show_num(uint8_t Line,uint8_t Column,uint32_t num ,uint8_t len ,uint8_t mode);

#endif
