/* assemble.h  header file for assemble.c
*
* The Netwide Assembler is copyright (C) 1996 Simon Tatham and
* Julian Hall. All rights reserved. The software is
* redistributable under the licence given in the file "Licence"
* distributed in the NASM archive.
*/
/*
*   ����parser.c����insn�ṹ��assemble.c�Ͱ���Intel�������������ʵ�ʵ�
*   �����룬������out*.c�����ɾ����ʽ��Ŀ���ļ���
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
			   *     ����insn_sizeһ�����ڵ�һ�����Դ��ʱ������ȷ��ĳһ�д�����ʵ��Ŀ���ļ��������
			   *   �ռ䣬��assemble��һ�����ڵڶ������Դ��ʱ����ת��insn�ṹ�е�ָ��Ϊʵ�ʵĻ����룬
			   *   �������out*.c�������ɾ����ʽ��Ŀ���ļ���
*/