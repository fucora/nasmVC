/* float.h   header file for the floating-point constant module of
 * 	     the Netwide Assembler
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */

#ifndef NASM_FLOAT_H
#define NASM_FLOAT_H
//float.cģ�鵼��һ������float_const��
int float_const (char *number, long sign, unsigned char *result, int bytes,
		 efunc error);

#endif

/*
 *�����������ָ��DD, DQ��DT��ĸ���������ת��ΪIntel�����ڲ������ݱ����ʽ��
 *       float.c��ʶ��ĸ�������ʽ���£�
 *         dd   1.2               ; an easy one
 *         dq   1.e10             ; 10,000,000,000
 *         dq   1.e+10             ; synonymous with 1.e10
 *         dq   1.e-10             ; 0.000 000 000 1
 *         dt   3.141592653589793238462 ; pi
 *       ��Ҫע�����NASM���ṩ�������ı��ʽ��ֵ���㣬������ΪNASM��Ϊ���ܱ�֤����
 *   ����ANSI C�������ĵ�ϵͳ���ṩ����������Ŀ⺯�������Լ�ʵ�����е�ò���ʧ��
 */