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
//float.c模块导出一个函数float_const：
int float_const (char *number, long sign, unsigned char *result, int bytes,
		 efunc error);

#endif

/*
 *这个函数负责将指令DD, DQ和DT后的浮点数常量转换为Intel机器内部的数据表达形式。
 *       float.c能识别的浮点数格式如下：
 *         dd   1.2               ; an easy one
 *         dq   1.e10             ; 10,000,000,000
 *         dq   1.e+10             ; synonymous with 1.e10
 *         dq   1.e-10             ; 0.000 000 000 1
 *         dt   3.141592653589793238462 ; pi
 *       需要注意的是NASM不提供浮点数的表达式求值运算，这是因为NASM认为不能保证所有
 *   存在ANSI C编译器的的系统都提供浮点数运算的库函数，而自己实现又有点得不偿失。
 */