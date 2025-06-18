
#ifndef __DATATYPE_H__
#define __DATATYPE_H__

typedef unsigned char INT8U; 		// �޷���8λ���ͱ��� //

typedef signed char INT8S; 			// �з���8λ���ͱ��� //

typedef unsigned int INT16U; 		// �޷���16λ���ͱ��� //

typedef signed int INT16S; 			// �з���16λ���ͱ��� //

typedef unsigned long INT32U; 		// �޷���32λ���ͱ��� //

typedef signed long INT32S; 		// �з���32λ���ͱ��� //

typedef float FP32; 				// �����ȸ�����(32λ����) //

typedef double FP64; 				// ˫���ȸ�����(64λ����) //

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
