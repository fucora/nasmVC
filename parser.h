/* parser.h   header file for the parser module of the Netwide
 *            Assembler
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */

#ifndef NASM_PARSER_H
#define NASM_PARSER_H

void parser_global_info (struct ofmt *output, loc_t *locp);
insn *parse_line (int pass, char *buffer, insn *result,
		  efunc error, evalfunc evaluate, ldfunc ldef);
void cleanup_insn (insn *instruction);

#endif

/*
 *     其中parser_global_info用于解析前的初始化工作(这里是初始化输出的文件格式和
 *     当前行所在的位置，在定义标号时需要用到)。cleanup_insn用于解析后的清理工作。
 *
 *     而parse_line的功能就是按照上面提到的`标号',`指令',`操作数'和`注释'的
 *   顺序对buffer里的代码进行解析，并对相应部分的合法性做一些检查，比如检查指令的前缀是
 *   不是超过了所能允许的最大值，操作数是否为内存地址，代码中是否含有一个向前的引用等。
 *   它还提供了对伪指令DB,DD,RESB,RESD,INCBIN等的支持。
 */