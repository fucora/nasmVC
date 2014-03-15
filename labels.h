/* labels.h  header file for labels.c
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */
/*
 *       NASM�ı�ŷ־ֲ���ź�ȫ�ֱ������(�ⲿ��ſɿ���������һ��Դ�����е�ȫ�ֱ��)��
 *       �ֲ���������ս�����������ɣ�"��һ��ȫ�ֱ�������ֲ������"��
 *       ȫ�ֱ�������ս�����������ɣ�"lprefix+ȫ�ֱ����+lpostfix"������lprefix��lpostfix
 *   ���ǿ�ѡ�ģ����Ƿֱ����������е�ȫ�ֱ������ǰ��ͺ�������ַ����������ڱ���ʱָ��ѡ��
 *   --prefix_ ���������ڵ�ȫ�ֱ����ǰ���»��ߣ���ͻ����C�����ɱ�ŵ������ࡣ
 *       ����lable.c�Ὣ��ŵ������Ϣ������Ӧ��out*.c������Ŀ���ļ��еķ��š�
 *
 *       ���ģ�鵼���������ݺͺ�����
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
 *   ��������init_labels��cleanup_labels�ֱ������ڲ����ݵĳ�ʼ������������
 *   ��������lookup_label���ڲ��Ҵ��ڵı�Ų����ض�Ӧ�Ķκ�ƫ�Ƶ�ֵ��
 *   ��������define_label���ڶ����Ų�����Ϣ���ݸ���Ӧ��out*.c������Ŀ���ļ��еķ��š�
 *       ����redefine_label���ڼ�����Ƿ���ڶ�λ���󲢶����������(�����ߵ�˵������Ȼ���
 *       ���Ļ����������������ܣ�����������񲢲�����ʲô����)��
 */