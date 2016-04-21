#include "Huffman.h"
#include<iostream>
using namespace std;
int Select(HuffmanTree pHT, int nSize);
//����HuffmanTree
void HuffmanTreeInit(HuffmanTree pHT, int w[])
{
	//��ʼ��HuffmanTree
	for (int i = 1; i < 512; i++)
	{
		if (i <= 256)
		{
			pHT[i].weight = *w++;
			pHT[i].c = i-1;
		}
		else
			pHT[i].weight = 2147483647;
		pHT[i].lchild = 0;
		pHT[i].rchild = 0;
		pHT[i].parent = 0;
	}
	//��weight[]�����е���Ϣ����HuffmanTree
	for (int i = 257; i < 512; i++)
	{
		int min = Select(pHT, i - 1);
		pHT[min].parent = i;
		pHT[i].lchild = min;
		pHT[i].weight = pHT[min].weight;
		min = Select(pHT, i - 1);
		pHT[min].parent = i;
		pHT[i].rchild = min;
		pHT[i].weight = pHT[min].weight + pHT[i].weight;
	}
}
//ѡ����Сֵ
int Select(HuffmanTree pHT, int nSize)
{
	int minValue = 2147483647;	//��Сֵ
	int min = 0;				//Ԫ�����

	//�ҵ���СȨֵ��Ԫ�����к�
	for (int i = 1; i <= nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
		return min;
}
//��ʾÿ���ڵ����Ϣ
void TestHufTree(HuffmanTree pHT)
{
	for (int i = 1; i < 512; ++i)
	{
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}
//����ÿ���ڵ�
void TestHufTreeN(int root, HuffmanTree pHT)
{
	cout << pHT[root].weight << " ";
	if (pHT[root].lchild != 0)
	{
		TestHufTreeN(pHT[root].lchild, pHT);
	}
	if (pHT[root].rchild != 0)
	{
		TestHufTreeN(pHT[root].rchild, pHT);
	}
}
//��ʼ��HuffmanCode
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC)
{
	char* cd = (char*)malloc(256 * sizeof(char));
	cd[255] = '\0';
	for (int i = 1; i <= 256; ++i)
	{
		int start = 255;
		for (int c = i, f = pHT[i].parent; f != 0; c = f, f = pHT[f].parent)
			if (pHT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		pHC[i-1] = (char*)malloc((256 - start) * sizeof(char));
		strcpy(pHC[i-1], &cd[start]);
	}
	free(cd);
}

void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC)
{
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
		printf("0x%02X %s\n", root , pHC[root]);
	if (pHT[root].lchild)//��������
		TestHufCode(pHT[root].lchild, pHT, pHC);
	if (pHT[root].rchild)//�����Һ���
		TestHufCode(pHT[root].rchild, pHT, pHC);
}