#ifndef __DATATYPE_H__
#define __DATATYPE_H__

/**
 * @file    datatype.h
 * @brief   �����������Ͷ���ͷ�ļ���������Ƕ��ʽC��Ŀ
 * @note    ������׼����������͡��������ͼ����ñ���
 */

// ===================== �������ͱ��� =====================
typedef unsigned char  INT8U;   // �޷���8λ����
typedef signed   char  INT8S;   // �з���8λ����

typedef unsigned int   INT16U;  // �޷���16λ����
typedef signed   int   INT16S;  // �з���16λ����

typedef unsigned long  INT32U;  // �޷���32λ����
typedef signed   long  INT32S;  // �з���32λ����

typedef float          FP32;    // �����ȸ�����(32λ)
typedef double         FP64;    // ˫���ȸ�����(64λ)

// ===================== ��ȷ����������� =====================
typedef signed   char  int8_t;    // ��ȷ8λ�з�������
typedef signed   int   int16_t;   // ��ȷ16λ�з�������
typedef signed   long  int32_t;   // ��ȷ32λ�з�������
//typedef signed __INT64 int64_t; // ��ȷ64λ�з������ͣ�����֧�֣�

typedef unsigned char  uint8_t;   // ��ȷ8λ�޷�������
typedef unsigned int   uint16_t;  // ��ȷ16λ�޷�������
typedef unsigned long  uint32_t;  // ��ȷ32λ�޷�������
//typedef unsigned __INT64 uint64_t; // ��ȷ64λ�޷������ͣ�����֧�֣�

// ===================== ���ü�д���� =====================
typedef uint32_t  u32; // 32λ�޷������ͼ�д
typedef uint16_t  u16; // 16λ�޷������ͼ�д
typedef uint8_t   u8;  // 8λ�޷������ͼ�д

typedef int32_t   s32; // 32λ�з������ͼ�д
typedef int16_t   s16; // 16λ�з������ͼ�д
typedef int8_t    s8;  // 8λ�з������ͼ�д

#endif
