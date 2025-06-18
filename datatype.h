
#ifndef __DATATYPE_H__
#define __DATATYPE_H__

typedef unsigned char INT8U; 		// 无符号8位整型变量 //

typedef signed char INT8S; 			// 有符号8位整型变量 //

typedef unsigned int INT16U; 		// 无符号16位整型变量 //

typedef signed int INT16S; 			// 有符号16位整型变量 //

typedef unsigned long INT32U; 		// 无符号32位整型变量 //

typedef signed long INT32S; 		// 有符号32位整型变量 //

typedef float FP32; 				// 单精度浮点数(32位长度) //

typedef double FP64; 				// 双精度浮点数(64位长度) //

    /* exact-width signed integer types */
typedef   signed          char int8_t;
typedef   signed           int int16_t;
typedef	  signed 		  long int32_t;
//typedef   signed       __INT64 int64_t;

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned           int uint16_t;
typedef unsigned 		  long uint32_t;

//typedef unsigned       __INT64 uint64_t;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

#endif
