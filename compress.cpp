#include "huffman.h"
#include "compress.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
char name[] = "C:\Pic.bmp";
int weight[256] = { 0 };
void InitPicture() {

	
	FILE *in;
	errno_t err = fopen_s(&in, name, "rb");
	//strcpy_s(type, "huf");
	int ch, length = 0;
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
		length++;
	}

	//cout << "Byte" << "Weight" << endl;
	//for (int i = 0; i < 256; i++)
	//{
	//	printf("0x%02X %d\n", i, weight[i]);
	//}
	cout << "原文件为" << name << endl;
	cout << "长度为" << length << endl;
	fclose(in);
}
int compress() {
	InitPicture();
	HuffmanTree H;
	H = creat(weight, 256);
	creat_code(H, 256);
	//计算缓冲区大小
	int Nsize = 0;
	for (int i = 0; i < 256; i++)
	{
		Nsize += weight[i] * strlen(H[i].code);
	}
	Nsize = (Nsize % 8) ? Nsize / 8 + 1 : Nsize / 8;

	char *pBuffer = NULL;
	pBuffer = (char *)malloc(Nsize * sizeof(char));
	int pos=Encode(H, pBuffer, Nsize);
	if (!pBuffer)
	{
		return -1;
	}
	HEAD shead;
	InitHead(shead);
	int len=write(shead, pBuffer, pos);
	double xx = len * 100.0 / shead.length; 
	cout << "压缩后长度为" << len << endl;
	cout << "压缩率为" << xx << "%" << endl;
	
}
char Str2byte(const char *pBinStr) {
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		if (pBinStr[i]=='1')
		{
			b = b | 0x01;
		}

	}
	return b;
}
int Encode(HuffmanTree H, char *pBuffer, int size) {
	FILE *in;
	errno_t err = fopen_s(&in, name, "rb");
	
	char cd[256] = { '\0 '};
	int pos = 0;
	int ch;
	while (ch=fgetc(in)!=EOF)
	{
		
		strcat(cd, H[ch].code);
		while (strlen(cd)>=8)
		{
			pBuffer[pos++] = Str2byte(cd);
			for (int i = 0; i <256-8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd)>0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	fclose(in);
	return pos;

}
int InitHead( HEAD &shead) {
	strcpy(shead.type, "HUF");
	shead.length = 0;
	FILE *in;
	errno_t err = fopen_s(&in, name, "rb");
	//strcpy_s(type, "huf");
	int ch, length = 0;
	while ((ch = getc(in)) != EOF)
	{
		shead.weight[ch]++;
		shead.length++;
	}
	fclose(in);
	return 0;

}
int write(HEAD &shead, char *pBuffer, int size) {
	char filename[256] = { 0 };
	strcpy(filename, name);
	strcat(filename, ".huf");
	FILE *out = fopen(filename, "wb");
	fwrite(&shead, sizeof(HEAD), 1, out);
	fwrite(pBuffer, sizeof(char), size, out);
	fclose(out);
	cout << "生成压缩文件" << filename << endl;
	int len = sizeof(HEAD) + strlen(filename) + 1 + size;
	return len;
}