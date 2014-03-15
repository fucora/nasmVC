/* nasmlib.h	header file for nasmlib.c
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */
/*
 *       nasmlib.c提供如下函数：
 *       具有报错和记录功能的内存分配和释放函数;
 *       字符串和数字间的转换和赋值函数;
 *       对动态分配的随机存储数组(RAA)和顺序存储数组(SAA)进行管理的函数;
 *       一个标准的源码扫描函数;
 *       表达式处理的库函数;
 *       为目标文件自动添加扩展名的函数;
 *       对源码和目标文件提供支持的其它函数。
 */

/*
 *     (3)NASM在运行时会动态分配两块内存。一块用来进行随机内存存取，以树状结构表示，　
 *        每个叶结点中存储实际的数据；另一块用来进行顺序内存存取，以链状结构表示。
 *        这样程序在需要许多小的内存块时就不必每次去分配，只在已分配的内存块被用
 *        完时再分配。即提高了效率，也易于管理。
 *        (注：SAA:dynamic sequential-access array.
 *              RAA:dynamic random access array.)
 */
#ifndef NASM_NASMLIB_H
#define NASM_NASMLIB_H

/*
 * If this is defined, the wrappers around malloc et al will
 * transform into logging variants, which will cause NASM to create
 * a file called `malloc.log' when run, and spew details of all its
 * memory management into that. That can then be analysed to detect
 * memory leaks and potentially other problems too.
 */
/* #define LOGALLOC */

/*
 * Wrappers around malloc, realloc and free. nasm_malloc will
 * fatal-error and die rather than return NULL; nasm_realloc will
 * do likewise, and will also guarantee to work right on being
 * passed a NULL pointer; nasm_free will do nothing if it is passed
 * a NULL pointer.
 */
#ifdef NASM_NASM_H		       /* need efunc defined for this */
void nasm_set_malloc_error (efunc);
#ifndef LOGALLOC
void *nasm_malloc (size_t);
void *nasm_realloc (void *, size_t);
void nasm_free (void *);
char *nasm_strdup (char *);
char *nasm_strndup (char *, size_t);
#else
void *nasm_malloc_log (char *, int, size_t);
void *nasm_realloc_log (char *, int, void *, size_t);
void nasm_free_log (char *, int, void *);
char *nasm_strdup_log (char *, int, char *);
char *nasm_strndup_log (char *, int, char *, size_t);
#define nasm_malloc(x) nasm_malloc_log(__FILE__,__LINE__,x)
#define nasm_realloc(x,y) nasm_realloc_log(__FILE__,__LINE__,x,y)
#define nasm_free(x) nasm_free_log(__FILE__,__LINE__,x)
#define nasm_strdup(x) nasm_strdup_log(__FILE__,__LINE__,x)
#define nasm_strndup(x,y) nasm_strndup_log(__FILE__,__LINE__,x,y)
#endif
#endif

/*
 * ANSI doesn't guarantee the presence of `stricmp' or
 * `strcasecmp'.
 */
int nasm_stricmp (const char *, const char *);
int nasm_strnicmp (const char *, const char *, int);

/*
 * Convert a string into a number, using NASM number rules. Sets
 * `*error' to TRUE if an error occurs, and FALSE otherwise.
 */
long readnum(char *str, int *error);

/*
 * Convert a character constant into a number. Sets
 * `*warn' to TRUE if an overflow occurs, and FALSE otherwise.
 * str points to and length covers the middle of the string,
 * without the quotes.
 */
long readstrnum(char *str, int length, int *warn);

/*
 * seg_init: Initialise the segment-number allocator.
 * seg_alloc: allocate a hitherto unused segment number.
 */
void seg_init(void);
long seg_alloc(void);

/*
 * many output formats will be able to make use of this: a standard
 * function to add an extension to the name of the input file
 */
#ifdef NASM_NASM_H
void standard_extension (char *inname, char *outname, char *extension,
			 efunc error);
#endif

/*
 * some handy macros that will probably be of use in more than one
 * output format: convert integers into little-endian byte packed
 * format in memory
 */

#define WRITELONG(p,v) \
  do { \
    *(p)++ = (v) & 0xFF; \
    *(p)++ = ((v) >> 8) & 0xFF; \
    *(p)++ = ((v) >> 16) & 0xFF; \
    *(p)++ = ((v) >> 24) & 0xFF; \
  } while (0)

#define WRITESHORT(p,v) \
  do { \
    *(p)++ = (v) & 0xFF; \
    *(p)++ = ((v) >> 8) & 0xFF; \
  } while (0)

/*
 * and routines to do the same thing to a file
 */
void fwriteshort (int data, FILE *fp);
void fwritelong (long data, FILE *fp);

/*
 * Routines to manage a dynamic random access array of longs which
 * may grow in size to be more than the largest single malloc'able
 * chunk.
 */

#define RAA_BLKSIZE 4096	       /* this many longs allocated at once */
#define RAA_LAYERSIZE 1024	       /* this many _pointers_ allocated */

typedef struct RAA RAA;
typedef union RAA_UNION RAA_UNION;
typedef struct RAA_LEAF RAA_LEAF;
typedef struct RAA_BRANCH RAA_BRANCH;

//Random  Access Array 随机访问数组，这是一个树状结构。
struct RAA {
    /*
     * Number of layers below this one to get to the real data. 0
     * means this structure is a leaf, holding RAA_BLKSIZE real
     * data items; 1 and above mean it's a branch, holding
     * RAA_LAYERSIZE pointers to the next level branch or leaf
     * structures.
     */
	//1---这是一个树枝，包含LAYERSIZE 各指针。0---一个叶子，含有
	//RAA_BLKSIZE各实际数字。数据包含在下面的data里
    int layers;
    /*
     * Number of real data items spanned by one position in the
     * `data' array at this level. This number is 1, trivially, for
     * a leaf (level 0): for a level 1 branch it should be
     * RAA_BLKSIZE, and for a level 2 branch it's
     * RAA_LAYERSIZE*RAA_BLKSIZE.
     */
    /*
     * stepsize=1,这是一个叶子节点
     * 对于第一层的树枝,stepsize= RAA_BLKSIZE
     *对于第二层的树枝,stepsize= RAA_LAYERSIZE*RAA_BLKSIZE.
     */
    long stepsize;
	//下面是存放数据的地方
    union RAA_UNION {
		struct RAA_LEAF {
			long data[RAA_BLKSIZE];
		} l;
		struct RAA_BRANCH {
			struct RAA *data[RAA_LAYERSIZE];
		} b;
    } u;
};


struct RAA *raa_init (void);
void raa_free (struct RAA *);
long raa_read (struct RAA *, long);
struct RAA *raa_write (struct RAA *r, long posn, long value);

/*
 * Routines to manage a dynamic sequential-access array, under the
 * same restriction on maximum mallocable block. This array may be
 * written to in two ways: a contiguous chunk can be reserved of a
 * given size, and a pointer returned, or single-byte data may be
 * written. The array can also be read back in the same two ways:
 * as a series of big byte-data blocks or as a list of structures
 * of a given size.
 */

//dynamic sequential-access array动态顺序访问数组。
//这是一个双向链表结构。Next,end为前向指针，后向指针。注意end存储了当前的位置(pos)
//和起点（start）。
//elem_len---每一个元素的大小
//length，该节点可存储数据的长度
//posn----相对start的偏移。
//rptr,rpos读操作使用
//data存储数据。
struct SAA {
    /*
     * members `end' and `elem_len' are only valid in first link in
     * list; `rptr' and `rpos' are used for reading
     */
    struct SAA *next, *end, *rptr;
    long elem_len, length, posn, start, rpos;
    char *data;
};

//初始化SAA,元素的长度为elem_len
struct SAA *saa_init (long elem_len);  /* 1 == byte */
void saa_free (struct SAA *);//释放SAA的空间

//写一个元素（长度为elem_len）,并返回写该元素数据的起始位置。
void *saa_wstruct (struct SAA *);      /* return a structure of elem_len */

//在SAA中写数据，data未数据地址，len为长度。
void saa_wbytes (struct SAA *, void *, long);  /* write arbitrary bytes */

//把读操作指针指向头部。
void saa_rewind (struct SAA *);	       /* for reading from beginning */

//读一个元素，返回该元素的头部指针。
void *saa_rstruct (struct SAA *);      /* return NULL on EOA */

//读一个元素，并len返回元素长度。返回值为该数据首地址
void *saa_rbytes (struct SAA *, long *);   /* return 0 on EOA */

//从SAA中读取len长度到data中。
void saa_rnbytes (struct SAA *, void *, long); /* read a given no. of bytes */

//从SAA中的数据偏移posn 的地方读取len长度的数据到len.这是相对所有存放的数据开始的偏移，
//和前面从当前位置不同。
void saa_fread (struct SAA *s, long posn, void *p, long len);   /* fixup */

//在偏移为posn的地方写入长度为len数据data.
void saa_fwrite (struct SAA *s, long posn, void *p, long len);   /* fixup */
void saa_fpwrite (struct SAA *, FILE *);

#ifdef NASM_NASM_H
/*
 * Standard scanner.
 */
extern char *stdscan_bufptr;
void stdscan_reset(void);
int stdscan (void *private_data, struct tokenval *tv);
#endif

#ifdef NASM_NASM_H
/*
 * Library routines to manipulate expression data types.
 */
int is_reloc(expr *);
int is_simple(expr *);
int is_really_simple (expr *);
int is_unknown(expr *);
int is_just_unknown(expr *);
long reloc_value(expr *);
long reloc_seg(expr *);
long reloc_wrt(expr *);
#endif

/*
 * Binary search routine. Returns index into `array' of an entry
 * matching `string', or <0 if no match. `array' is taken to
 * contain `size' elements.
 */
int bsi (char *string, char **array, int size);


char *src_set_fname(char *newname);
long src_set_linnum(long newline);
long src_get_linnum(void);
/*
 * src_get may be used if you simply want to know the source file and line.
 * It is also used if you maintain private status about the source location
 * It return 0 if the information was the same as the last time you
 * checked, -1 if the name changed and (new-old) if just the line changed.
 */
int src_get(long *xline, char **xname);

void nasm_quote(char **str);
char *nasm_strcat(char *one, char *two);
void nasmlib_cleanup(void);

void null_debug_routine();
extern struct dfmt null_debug_form;
extern struct dfmt *null_debug_arr[2];
#endif
