#ifndef __DATATYPE_H__
#define __DATATYPE_H__

/**
 * @file    datatype.h
 * @brief   常用数据类型定义头文件，适用于嵌入式C项目
 * @note    包含标准宽度整数类型、浮点类型及常用别名
 */

// ===================== 基本类型别名 =====================
typedef unsigned char  INT8U;   // 无符号8位整型
typedef signed   char  INT8S;   // 有符号8位整型

typedef unsigned int   INT16U;  // 无符号16位整型
typedef signed   int   INT16S;  // 有符号16位整型

typedef unsigned long  INT32U;  // 无符号32位整型
typedef signed   long  INT32S;  // 有符号32位整型

typedef float          FP32;    // 单精度浮点数(32位)
typedef double         FP64;    // 双精度浮点数(64位)

// ===================== 精确宽度整数类型 =====================
typedef signed   char  int8_t;    // 精确8位有符号整型
typedef signed   int   int16_t;   // 精确16位有符号整型
typedef signed   long  int32_t;   // 精确32位有符号整型
//typedef signed __INT64 int64_t; // 精确64位有符号整型（如需支持）

typedef unsigned char  uint8_t;   // 精确8位无符号整型
typedef unsigned int   uint16_t;  // 精确16位无符号整型
typedef unsigned long  uint32_t;  // 精确32位无符号整型
//typedef unsigned __INT64 uint64_t; // 精确64位无符号整型（如需支持）

// ===================== 常用简写别名 =====================
typedef uint32_t  u32; // 32位无符号整型简写
typedef uint16_t  u16; // 16位无符号整型简写
typedef uint8_t   u8;  // 8位无符号整型简写

typedef int32_t   s32; // 32位有符号整型简写
typedef int16_t   s16; // 16位有符号整型简写
typedef int8_t    s8;  // 8位有符号整型简写

#endif
