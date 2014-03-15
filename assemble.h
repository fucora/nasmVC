/* assemble.h  header file for assemble.c
*
* The Netwide Assembler is copyright (C) 1996 Simon Tatham and
* Julian Hall. All rights reserved. The software is
* redistributable under the licence given in the file "Licence"
* distributed in the NASM archive.
*/
/*
*   　当parser.c填充好insn结构后，assemble.c就按照Intel机器码规则生成实际的
*   机器码，并传给out*.c来生成具体格式的目标文件。
*/

#ifndef NASM_ASSEMBLE_H
#define NASM_ASSEMBLE_H

long insn_size (long segment, long offset, int bits,
				insn *instruction, efunc error);
long assemble (long segment, long offset, int bits,
			   insn *instruction, struct ofmt *output, efunc error,
			   ListGen *listgen);

#endif

			   /*
			   *     其中insn_size一般用在第一遍分析源码时，用于确定某一行代码在实际目标文件中所需的
			   *   空间，而assemble则一般用在第二遍分析源码时，它转化insn结构中的指令为实际的机器码，
			   *   并输出到out*.c中以生成具体格式的目标文件。
*/