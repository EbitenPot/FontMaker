/*
* �ַ����������,�����һ�����飬�����ԱΪUNICODE����
* ASCII:  0x00-0x7F
* ISO8859:0x00-0xFF
* GB2312: 0xA1A1 - 0xFEFE
* GBK:    HSB=0x81-0xFE,LSB=0x40-0x7E,0x80-0xFE
* BIG5:   HSB=0xA1-0xF9,LSB=0x40-0x7E,0xA1-0xFE
* HANGUL: HSB=0x81-0xFE,LSB=0x40-0x7E,0x80-0xFE
* ������ <kerndev@foxmail.com>
*/

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define FILE_NAME    "ISO8859-1.cst"
#define CODE_PAGE     28591
#define BYTE_BEGIN    0x00
#define BYTE_END      0xFF

//ANSI -> UNICODE
static WCHAR ansi_to_unicode(UINT code_page, CHAR *s)
{
	WCHAR output[8];
	MultiByteToWideChar(code_page, MB_USEGLYPHCHARS|MB_PRECOMPOSED,(LPCSTR)s, -1, output, 2);
	return output[0];
}

static void write_charset(FILE* fp)
{
	UINT i;
	CHAR s[4];
	WCHAR c;
	memset(s, 0, sizeof(s));
	for(i = BYTE_BEGIN; i <= BYTE_END; i++)
	{
		s[0] = i;
		c = ansi_to_unicode(CODE_PAGE, s);
		fwrite(&c, 1, 2, fp);
	}
}

void maker()
{
	FILE *fp;
	char *file_name = FILE_NAME;
	fp = fopen(file_name,"wb+");
	if(fp == NULL)
	{
		printf("�����ļ�ʧ��!\r\n");
		return;
	}
	write_charset(fp);
	fclose(fp);
	printf("��������ɹ�.\r\n");
}

void banner(void)
{
	printf("**********************************************\n");
	printf("* ������ɹ���\n");
	printf("* ������<kerndev@foxmail.com>\n");
	printf("* 2020.10.11\r\n");
	printf("**********************************************\n");
	printf("�������:%s\n", FILE_NAME);
	printf("����ҳ:  %d\n", CODE_PAGE);
}

void main(void)
{
	banner();
	maker();
	system("pause");
}