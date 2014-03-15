/* listing.h   header file for listing.c
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */
/*
 *       list.c���������б��ļ����б��ļ��ĸ�ʽ���£�
 *   ���������б��ļ����к� ������Ŀ���ļ��е�ƫ�� <�б�Ƕ�ײ���>��Դ�����л��չ����Ĵ���
 *
 *       ���е��б�Ƕ�ײ�������INCBIN,TIMES,INCLUDE��MACRO��αָ����ڱ�ʾ��Щָ��չ������
 *   ������Ƕ�׵Ĳ�������ʵ�����ɵ��б��ļ��в���TIMESָ���ָ����.nolist�ĺ����չ��������
 *
 *   ����list.c���⵼�����½ṹ��
 */

#ifndef NASM_LISTING_H
#define NASM_LISTING_H

extern ListGen nasmlist;

#endif

/*
 *   ��������list_init��list_cleanup�ֱ�����ģ���ڲ����ݵĳ�ʼ�������������
 *   ����list_output���������б��ļ���ʽ�еĵ�ǰ�����֣�list_line���������б��ļ���ʽ�е�
 *   �������֡�list_upleve��list_downlevel������ģ����ã��Ը���list.c�е��б�Ƕ�ײ�����
 *   ֵ��ע�����Դ���е����ݽṹMacroInhibitĿǰ��ģ���в�û��ʲôʵ�ʵ����ã�����list.c
 *   Ҳû�жԴ���Ĳ������г�ֵĴ��������ߵ�˵������Щ����ʵ�ֲ�û�о����ܺõĿ��ǣ�
 *   ����ֻ����Ϊ"����ܹ�����"�����Բű���������
 */