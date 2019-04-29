
#pragma once
struct  HEAD
{
	char type[4];
	int length;
	int weight[256];
};
int Encode(HuffmanTree H, char *pBuffer, int size);
int InitHead(HEAD &shead);
int compress();
int write(HEAD &shead, char *pBuffer, int size);