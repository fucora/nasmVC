/* preproc.h  header file for preproc.c
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */

/*
 *　　　 预处理部分是NASM中最复杂，也是代码最多的模块，有四千多行代码。
 *　 　　它使用自己的源码扫描程序ppscan，支持名字相同但参数不同的宏，支持
 *　　　 各个宏通过上下文相关堆栈来交换信息，支持宏内进行预处理循环等。
 *　　   (可参阅NASM使用文档来了解预处理的功能和使用方法)
*/

#ifndef NASM_PREPROC_H
#define NASM_PREPROC_H

void pp_include_path (char *);
void pp_pre_include (char *);
void pp_pre_define (char *);
void pp_pre_undefine (char *);
void pp_extra_stdmac (char **);

extern Preproc nasmpp;

#endif
