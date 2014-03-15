/* eval.h   header file for eval.c
*
* The Netwide Assembler is copyright (C) 1996 Simon Tatham and
* Julian Hall. All rights reserved. The software is
* redistributable under the licence given in the file "Licence"
* distributed in the NASM archive.
*/
/*
* 　　　　eval.c用于计算并返回代码中表达式的值，其中运算符||,^^,&&等用于条件汇编%if类指令
* 　　的表达式中，返回真或假，|,^,&,<<,+,*,/等用于对常量值进行运算，SEG，WRT等则用于得到
*   程序中段(或节)实际的基址和偏移。
*     eval.c的功能比较简单，不能像MASM那样处理类似(eax != 0)这样的表达式。(后记1)。
* 　　　　eval.c利用标准的scan程序扫描表达式缓冲区，找出存在的运算符进行运算，并将
* 　　处理后的值存入expr结构中：
*/

#ifndef NASM_EVAL_H
#define NASM_EVAL_H

/*
* Called once to tell the evaluator what output format is
* providing segment-base details, and what function can be used to
* look labels up.
*/
void eval_global_info (struct ofmt *output, lfunc lookup_label, loc_t *locp);

/*
* The evaluator itself.
*/
expr *evaluate (scanner sc, void *scprivate, struct tokenval *tv,
				int *fwref, int critical, efunc report_error,
				struct eval_hints *hints);

void eval_cleanup(void);

#endif
/*
*      值得注意的是eval.c只在第一遍分析源码时处理运算符||,^^，&&等，因为它们只在
*   预处理表达式中才可能出现。
*/