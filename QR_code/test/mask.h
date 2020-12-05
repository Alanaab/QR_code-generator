#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
////////////////////////////////////////////////////////////////////////////////////////
//������������ֵ�����
#include <pshpack2.h>
#include<string.h>
#include <pshpack2.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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






















void Eliminate_code(int(*mask)[200], int side)
{
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			if (i < 9 && j <9)//position detection pattern��format information���ֹ���
				mask[i][j] = 0;
			if (i>(side - 9) && j<9)
				mask[i][j] = 0;
			if (j>(side - 9) && i<9)
				mask[i][j] = 0;
			if (i == 6)//timing pattern���ֹ���
				mask[i][j] = 0;
			if (j == 6)
				mask[i][j] = 0;
			/*if (j == 8 && i == 0)//format information��������
				mask[i][j] = 1;
			if (j == 8 && i == 2)
				mask[i][j] = 1;
			if (j == 8 && i == 4)
				mask[i][j] = 1;
			if (j == 1 && i == 8)
				mask[i][j] = 1;
			if (j == 4 && i == 8)
				mask[i][j] = 1;
			if (j == (side - 1) && i == 8)
				mask[i][j] = 1;
			if (j == (side - 3) && i == 8)
				mask[i][j] = 1;
			if (j == (side - 5) && i == 8)
				mask[i][j] = 1;
			if (j == 8 && i == (side - 2))
				mask[i][j] = 1;
			if (j == 8 && i == (side - 5))
				mask[i][j] = 1;*/
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//�����ֵ����
int Score(int(*mask)[200], int(*E)[21], int side)
{
	int score = 0, sum0 = 0, sum = side*side, min;
	for (int i = 0; i < side; i++)//����ģ����XOR����
		for (int j = 0; j < side; j++)
			mask[i][j] = mask[i][j] ^ E[i][j];
	for (int i = 0; i < side; i++)//��ֵ�����һ��
		for (int j = 0; j < side - 5; j++)
			if (mask[i][j] + mask[i][j + 1] + mask[i][j + 2] + mask[i][j + 3] + mask[i][j + 4] == 5)
			{
				score += 3;
				if (j>0)
					if (mask[i][j - 1] + mask[i][j] + mask[i][j + 1] + mask[i][j + 2] + mask[i][j + 3] == 5)
						score -= 2;
			}
	for (int i = 0; i < side; i++)
		for (int j = 0; j < side - 5; j++)
			if (mask[i][j] + mask[i][j + 1] + mask[i][j + 2] + mask[i][j + 3] + mask[i][j + 4] == 0)
			{
				score += 3;
				if (j>0)
					if (mask[i][j - 1] + mask[i][j] + mask[i][j + 1] + mask[i][j + 2] + mask[i][j + 3] == 0)
						score -= 2;
			}
	for (int i = 0; i < side - 5; i++)
		for (int j = 0; j < side; j++)
			if (mask[i][j] + mask[i + 1][j] + mask[i + 2][j] + mask[i + 3][j] + mask[i + 4][j] == 5)
			{
				score += 3;
				if (i>0)
					if (mask[i - 1][j] + mask[i][j] + mask[i + 1][j] + mask[i + 2][j] + mask[i + 3][j] == 5)
						score -= 2;
			}
	for (int i = 0; i < side - 5; i++)
		for (int j = 0; j < side; j++)
			if (mask[i][j] + mask[i + 1][j] + mask[i + 2][j] + mask[i + 3][j] + mask[i + 4][j] == 0)
			{
				score += 3;
				if (i>0)
					if (mask[i - 1][j] + mask[i][j] + mask[i + 1][j] + mask[i + 2][j] + mask[i + 3][j] == 0)
						score -= 2;
			}
	for (int i = 0; i < side - 1; i++)//��ֵ����ڶ���
		for (int j = 0; j < side - 1; j++)
			if (mask[i][j] + mask[i][j + 1] + mask[i + 1][j] + mask[i + 1][j + 1] == 4)
				score += 3;
	for (int i = 0; i < side - 1; i++)
		for (int j = 0; j < side - 1; j++)
			if (mask[i][j] + mask[i][j + 1] + mask[i + 1][j] + mask[i + 1][j + 1] == 0)
				score += 3;
	for (int i = 0; i < side; i++)//��ֵ���������
		for (int j = 0; j < side - 10; j++)
		{
			if (mask[i][j] + mask[i][j + 1] + mask[i][j + 2] + mask[i][j + 3] + mask[i][j + 5] + mask[i][j + 9] == 0
				&& mask[i][j + 4] + mask[i][j + 6] + mask[i][j + 7] + mask[i][j + 8] + mask[i][j + 10] == 5)
				score += 40;
			if (mask[i][j] + mask[i][j + 2] + mask[i][j + 3] + mask[i][j + 4] + mask[i][j + 6] == 5
				&& mask[i][j + 1] + mask[i][j + 5] + mask[i][j + 7] + mask[i][j + 8] + mask[i][j + 9] + mask[i][j + 10] == 0)
				score += 40;
		}
	for (int i = 0; i < side - 10; i++)
		for (int j = 0; j < side; j++)
		{
			if (mask[i][j] + mask[i + 1][j] + mask[i + 2][j] + mask[i + 3][j] + mask[i + 5][j] + mask[i + 9][j] == 0
				&& mask[i + 4][j] + mask[i + 6][j] + mask[i + 7][j] + mask[i + 8][j] + mask[i + 10][j] == 5)
				score += 40;
			if (mask[i][j] + mask[i + 2][j] + mask[i + 3][j] + mask[i + 4][j] + mask[i + 6][j] == 5
				&& mask[i + 1][j] + mask[i + 5][j] + mask[i + 7][j] + mask[i + 8][j] + mask[i + 9][j] + mask[i + 10][j] == 0)
				score += 40;
		}
	for (int i = 0; i < side; i++)//��ֵ������Ĳ�
		for (int j = 0; j < side; j++)
			if (mask[i][j] == 0)
				sum0 += 1;
	min = abs(100.0 * sum0 / sum - 50) / 5;
	score += min * 10;
	return score;
}
//////////////////////////////////////////////////////////////////////////////////////
//ѡ�����ͷ�ֵ������
int Select(int(*mask)[200], int(*E)[21], int side)
{
	int s, k, min, num[8];
	for (int i = 0; i < side; i++)//����0��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			if ((i + j) % 2 == 0)//ȫͼ����
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[0] = Score(mask, E, side);
	for (int i = 0; i < side; i++)//����1��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			if (i % 2 == 0)
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[1] = Score(mask, E, side);
	for (int i = 0; i < side; i++)//����2��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			if (j % 3 == 0)
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[2] = Score(mask, E, side);
	for (int i = 0; i < side; i++)//����3��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			if ((i + j) % 3 == 0)
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[3] = Score(mask, E, side);
	for (int i = 0; i < side; i++)//����4��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			s = floor(i / 2) + floor(j / 3);
			if (s % 2 == 0)
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[4] = Score(mask, E, side);
	for (int i = 0; i < side; i++)//����5��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			if ((i * j) % 3 + (i*j) % 2 == 0)
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[5] = Score(mask, E, side);
	for (int i = 0; i < side; i++)//����6��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			if (((i * j) % 3 + (i*j) % 2) % 2 == 0)
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[6] = Score(mask, E, side);
	for (int i = 0; i < side; i++)//����7��
		for (int j = 0; j < side; j++)
		{
			mask[i][j] = 0;
			if (((i * j) % 3 + (i + j) % 2) % 2 == 0)
				mask[i][j] = 1;
		}
	Eliminate_code(mask, side);
	num[7] = Score(mask, E, side);
	min = num[0];
	for (int i = 0; i < 8; i++)
		if (num[i] < min)
			min = num[i];
	for (int i = 0; i < 8; i++)
		if (num[i] - min == 0)
			k = i;
	return k;
}
//////////////////////////////////////////////////////////////////////////////////////
//���
void Print(int(*mask)[200], int(*E)[21], int num, int side)
{
	int s;
	switch (num)
	{
	case 0:
		for (int i = 0; i < side; i++)//����0��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				if ((i + j) % 2 == 0)//ȫͼ����
					mask[i][j] = 1;
			}
		break;
	case 1:
		for (int i = 0; i < side; i++)//����1��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				if (i % 2 == 0)
					mask[i][j] = 1;
			}
		break;
	case 2:
		for (int i = 0; i < side; i++)//����2��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				if (j % 3 == 0)
					mask[i][j] = 1;
			}
		break;
	case 3:
		for (int i = 0; i < side; i++)//����3��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				if ((i + j) % 3 == 0)
					mask[i][j] = 1;
			}
		break;
	case 4:
		for (int i = 0; i < side; i++)//����4��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				s = floor(i / 2) + floor(j / 3);
				if (s % 2 == 0)
					mask[i][j] = 1;
			}
		break;
	case 5:
		for (int i = 0; i < side; i++)//����5��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				if ((i * j) % 3 + (i*j) % 2 == 0)
					mask[i][j] = 1;
			}
		break;
	case 6:
		for (int i = 0; i < side; i++)//����6��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				if (((i * j) % 3 + (i*j) % 2) % 2 == 0)
					mask[i][j] = 1;
			}
		break;
	case 7:
		for (int i = 0; i < side; i++)//����7��
			for (int j = 0; j < side; j++)
			{
				mask[i][j] = 0;
				if (((i * j) % 3 + (i + j) % 2) % 2 == 0)
					mask[i][j] = 1;
			}
		break;
	}
	Eliminate_code(mask, side);
	for (int i = 0; i < side; i++)//����ģ����XOR����
		for (int j = 0; j < side; j++)
			mask[i][j] = mask[i][j] ^ E[i][j];
	////////////////////////////////////////////////////////////////////////////////////////
	//��Ӿ�Ĭ��
	for (int i = side - 1; i >= 0; i--)
		for (int j = 0; j < side; j++)
			mask[i + 4][j] = mask[i][j];
	for (int i = 4; i < side + 4; i++)
		for (int j = side - 1; j >= 0; j--)
			mask[i][j + 4] = mask[i][j];
	for (int i = 0; i < side + 8; i++)
		for (int j = 0; j < side + 8; j++)
		{
			if (i < 4)
				mask[i][j] = 0;
			if (i > (side + 3))
				mask[i][j] = 0;
			if (j < 4)
				mask[i][j] = 0;
			if (j > side + 3)
				mask[i][j] = 0;
		}
	///////////////////////////////////////////////////////////////////////////////////
	//�ڰ׿����
		//int i = 0, j = 0;
	int mask1[300][300] = { 0 };
	for (int i = 0; i < (side+8 ); i++)
		for (int j = 0; j < (side+8 ); j++)
			for (int a = 0; a < 8; a++)
				for (int b = 0; b < 8; b++)
					mask1[i * 8 + a][j * 8 + b] = mask[i][j];
	struct
	{
		BYTE b;
		BYTE g;
		BYTE r;

	}

	pRGB[232][232];  // ����λͼ����
	memset(pRGB, 255, sizeof(pRGB)); // ���ñ���Ϊ��ɫ


	// ����ά��
	/*for (i = 0; i < 240; i++)
	{
		for (j = 0; j < 240; j++)
		{
			//	pRGB[i][j].r = 0xff;
			pRGB[i][j].r = 0xff;
			pRGB[i][j].g = 0xff;
			pRGB[i][j].b = 0xff;	

		}


	}*/
	for (int i = 0; i < (side+8 )*8; i++)
	{
		for (int j = 0; j < (side+8 )*8; j++)
		{
			if (mask1[i][j] == 1)
				pRGB[i][j].r = 0x00;
				pRGB[i][j].g = 0x00;
				pRGB[i][j].b = 0x00;
			if (mask1[i][j] == 0)
				pRGB[i][j].r = 0xff;
				pRGB[i][j].g = 0xff;
				pRGB[i][j].b = 0xff;
			//printf("��");
		}
		printf("\n");
	}

	generateBmp((BYTE*)pRGB,232, 232, "D:\\test.bmp");
}



	
	




	void Format_information_fill(int(*E)[21], int num, int side)
{
	int format[8][15] = {
		{ 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 }
	};
	/*for (int i = 0; i < 8; i++)
		E[8][side - 1 - i] = format[num][i];
	for (int i = 8; i < 15; i++)
		E[side - 15 + i][8] = format[num][i];*/
	for (int i = 0; i < 7; i++)
		E[side - 1 - i][8] = format[num][i];
	for (int i = 7; i < 15; i++)
		E[8][side - 15 + i] = format[num][i];
	E[0][8] = E[8][side - 1];
	E[1][8] = E[8][side - 2];
	E[2][8] = E[8][side - 3];
	E[3][8] = E[8][side - 4];
	E[4][8] = E[8][side - 5];
	E[5][8] = E[8][side - 6];
	E[7][8] = E[8][side - 7];
	E[8][8] = E[8][side - 8];
	E[8][7] = E[side - 7][8];
	E[8][5] = E[side - 6][8];
	E[8][4] = E[side - 5][8];
	E[8][3] = E[side - 4][8];
	E[8][2] = E[side - 3][8];
	E[8][1] = E[side - 2][8];
	E[8][0] = E[side - 1][8];
}