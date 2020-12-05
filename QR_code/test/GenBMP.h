#pragma once
#include <pshpack2.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include"mask.h"
#include"fill.h"
#include"Rs_code.h"
typedef long BOOL;
typedef long LONG;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;
//λͼ�ļ�ͷ�ļ�����
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ�Ķ�ȡ�ļ���Ϣ��

typedef struct
{
	WORD    bfType;//�ļ����ͣ�������0x424D,���ַ���BM��
	DWORD   bfSize;//�ļ���С
	WORD    bfReserved1;//������
	WORD    bfReserved2;//������
	DWORD   bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���
}
BMPFILEHEADER_T;

struct BMPFILEHEADER_S
{

	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;

};

typedef struct
{


	DWORD      biSize;//��Ϣͷ��С
	LONG       biWidth;//ͼ����
	LONG       biHeight;//ͼ��߶�
	WORD       biPlanes;//λƽ����������Ϊ1
	WORD       biBitCount;//ÿ����λ��
	DWORD      biCompression;//ѹ������
	DWORD      biSizeImage;//ѹ��ͼ���С�ֽ���
	LONG       biXPelsPerMeter;//ˮƽ�ֱ���
	LONG       biYPelsPerMeter;//��ֱ�ֱ���
	DWORD      biClrUsed;//λͼʵ���õ���ɫ����
	DWORD      biClrImportant;//��λͼ����Ҫ��ɫ����

}
BMPINFOHEADER_T;//λͼ��Ϣͷ����

void generateBmp(BYTE * pData, int width, int height, char * filename)//����BmpͼƬ������RGBֵ������ͼƬ���ش�С������ͼƬ�洢·��
{
	int size = width * height * 3; // ÿ�����ص�3���ֽ�
	// λͼ��һ���֣��ļ���Ϣ
	BMPFILEHEADER_T bfh;

	bfh.bfType = 0X4d42;  //bm
	bfh.bfSize = size  // data size
		+ sizeof(BMPFILEHEADER_T) // first section size

		+ sizeof(BMPINFOHEADER_T);// second section size

	bfh.bfReserved1 = 0; // reserved
	bfh.bfReserved2 = 0; // reserved
	bfh.bfOffBits = bfh.bfSize - size;


	// λͼ�ڶ����֣�������Ϣ

	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;
	FILE * fp = fopen(filename, "wb");
	if (!fp) return;
	fwrite(&bfh, 1, sizeof(BMPFILEHEADER_T), fp);
	fwrite(&bih, 1, sizeof(BMPINFOHEADER_T), fp);
	fwrite(pData, 1, size, fp);
	fclose(fp);

}




void Genbmp()
{
	int i = 0, j = 0;
	struct
	{
		BYTE b;
		BYTE g;
		BYTE r;

	}
	pRGB[240][240];  // ����λͼ����
	memset(pRGB, 0, sizeof(pRGB)); // ���ñ���Ϊ��ɫ


	// ���м仭һ��100*100�ľ���
	for (i = 0; i < 240; i++)
	{
		for (j = 0; j < 240; j++)
		{
			//	pRGB[i][j].r = 0xff;
			pRGB[i][j].r = 0xff;
			pRGB[i][j].g = 0xff;
			pRGB[i][j].b = 0xff;

		}


	}


	generateBmp((BYTE*)pRGB, 240, 240, "D:\\kkkk.bmp");// ����BMPͼƬ

}