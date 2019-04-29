#include "huffman.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

//void DoCode(char c[], HuffmanTree H, int m, int a);

HuffmanTree creat(int *w, int n)
{
	int number = 2 * n - 1;
	HuffmanTree HT = (HuffmanTree)malloc(2000 * sizeof(HTNode));
	if (!HT)
	{
		cout << "申请空间失败" << endl;
		exit(-1);
	}
	int i;
	for (i = 0; i < n; i++)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		//HT[i].n = now[i];
		HT[i].weight = *w;
		w++;
	}
	for (; i < number; i++)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = 0;
	}
	int min1, min2;
	for (i = n; i < number; i++)
	{
		min1 = chose_min(HT, i);
		min2 = chose_min(HT, i);
		HT[min1].parent = i;
		HT[min2].parent = i;
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
	}
	//for (int i = 0; i < number; i++)
	//{
	//			cout<< i<< " "<< HT[i].weight <<" "<< HT[i].parent <<" "<< HT[i].lchild <<" "<< HT[i].rchild <<" "<< endl;
		        //printf("HT[%d]\t\d\t\d\t\d\t\d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	//}

	return HT;
}
int chose_min(HuffmanTree HT, int m) {
	int i = 0;
	while (HT[i].parent != -1)
	{
		i++;
	}
	int min = i;
	int min_w = HT[i].weight;
	for (; i < m; ++i)
	{
		if ((HT[i].weight<min_w) && HT[i].parent == -1)
		{
			min_w = HT[i].weight;
			min = i;
		}
	}
	HT[min].parent = 1;
	return min;
}

void creat_code(HuffmanTree H, int n)
{
	ofstream CODE;
	CODE.open("CODE.txt", ios::trunc);
	char *code = (char*)malloc(2000 * sizeof(char));
	//cout << "code" << endl;
	int f,c;
	
	
	for (int i = 0; i < n; i++)
	{
		int start = n - 1;
		//H[i].code[n - 1] = '\0';
		char a[255] = { '\0' };
		c = i;
		f = H[i].parent;
		while (f!=-1)
		{
			if (H[f].lchild==c)
			{
				//H[i].code[--start] = '0';//如果是左孩子，则编码为0
				a[--start] = '0';
			}
			else
			{
				//H[i].code[--start] = '1';//如果是右孩子，则编码为1
				a[--start] = '1';
			}
			c = f;
			f = H[f].parent;
		}
		
		strcpy(H[i].code, &a[start]);
	
		string aa = H[i].code;
		aa = aa.substr(0, n - start-1);
		for (int j = 0; j < n - start; j++)
			{
				H[i].code[j] = aa[j];
			}
		H[i].code[n - start] = '\0';
       // cout << H[i].code << endl;
		CODE << "H[" << i << "].code=" << H[i].code << endl;
	
	}

	//system("pause");
	CODE.close();
}
/*
void DoCode(char c[], HuffmanTree H, int m, int a)
{
	char v[20] = { '\0' };
	int w = 0;
	for (int i = 0; i < a; )
	{
		int s = 2 * m - 2;
		while (H[s].lchild != -1 || H[s].rchild != -1)
		{
			if (c[i] == '0') {
				s = H[s].lchild;
				i++;
			}
			else {
				s = H[s].rchild;
				i++;
			}
		}
		if (H[s].lchild == -1 && H[s].rchild == -1)
		{
			v[w] = H[s].n;
			w++;
		}
		else
		{
			cout << "请输入正确的01编码" << endl;
		}

	}
	cout << "解码结果为";
	for (int i = 0; i < w; i++)
	{
		cout << v[i] << " ";
	}
}*/