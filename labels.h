/* labels.h  header file for labels.c
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */
/*
 *       NASM的标号分局部标号和全局标号两种(外部标号可看作是在另一个源程序中的全局标号)。
 *       局部标号名最终将由两部分组成："上一个全局标号名＋局部标号名"。
 *       全局标号名最终将由三部分组成："lprefix+全局标号名+lpostfix"。其中lprefix和lpostfix
 *   都是可选的，它们分别用于在所有的全局标号名的前面和后面添加字符串。比如在编译时指定选项
 *   --prefix_ 将会在所在的全局标号名前加下划线，这就会和在C中生成标号的情况差不多。
 *       最终lable.c会将标号的相关信息传给对应的out*.c来生成目标文件中的符号。
 *
 *       这个模块导出以下数据和函数：
 */

int lookup_label (char *label, long *segment, long *offset);
int is_extern (char *label);
void define_label (char *label, long segment, long offset, char *special,
		   int is_norm, int isextrn, struct ofmt *ofmt, efunc error);
void redefine_label (char *label, long segment, long offset, char *special,
		   int is_norm, int isextrn, struct ofmt *ofmt, efunc error);
void define_common (char *label, long segment, long size, char *special,
		    struct ofmt *ofmt, efunc error);
void declare_as_global (char *label, char *special, efunc error);
int init_labels (void);
void cleanup_labels (void);

/*
 *   　　函数init_labels和cleanup_labels分别用于内部数据的初始化和清理工作。
 *   　　函数lookup_label用于查找存在的标号并返回对应的段和偏移的值。
 *   　　函数define_label用于定义标号并将信息传递给相应的out*.c来生成目标文件中的符号。
 *       函数redefine_label用于检查标号是否存在定位错误并对其进行修正(按作者的说法，虽然大多
 *       数的汇编器都存在这个功能，但在这里好像并不能起到什么作用)。
 */