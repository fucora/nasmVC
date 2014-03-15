/* listing.h   header file for listing.c
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */
/*
 *       list.c用于生成列表文件。列表文件的格式如下：
 *   　　　　列表文件的行号 代码在目标文件中的偏移 <列表嵌套层数>　源代码行或宏展开后的代码
 *
 *       其中的列表嵌套层数用于INCBIN,TIMES,INCLUDE和MACRO等伪指令，用于表示这些指令展开后在
 *   代码中嵌套的层数。在实际生成的列表文件中不对TIMES指令和指定了.nolist的宏进行展开操作。
 *
 *   　　list.c对外导出如下结构：
 */

#ifndef NASM_LISTING_H
#define NASM_LISTING_H

extern ListGen nasmlist;

#endif

/*
 *   　　其中list_init和list_cleanup分别用于模块内部数据的初始化和清理操作。
 *   　　list_output用于生成列表文件格式中的的前两部分，list_line用于生成列表文件格式中的
 *   后两部分。list_upleve和list_downlevel被其它模块调用，以更新list.c中的列表嵌套层数。
 *   值得注意的是源码中的数据结构MacroInhibit目前在模块中并没有什么实际的作用，而且list.c
 *   也没有对传入的参数进行充分的处理。按作者的说法，这些函数实现并没有经过很好的考虑，
 *   它们只是因为"差不多能够工作"，所以才被保留至今。
 */