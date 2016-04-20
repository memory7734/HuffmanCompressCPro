#include "Huffman.h"
#include<iostream>
using namespace std;
int Select(HuffmanTree pHT, int nSize);
void HuffmanTreeInit(HuffmanTree pHT, int w[])
{
	for (int i = 1; i < 512; i++)
	{
		if (i <= 256)
			pHT[i].weight = *w++;
		else
			pHT[i].weight = 2147483647;
		pHT[i].lchild = 0;
		pHT[i].rchild = 0;
		pHT[i].parent = 0;
	}
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

int Select(HuffmanTree pHT, int nSize)
{
	int minValue = 2147483647;	//最小值
	int min = 0;				//元素序号

	//找到最小权值的元素序列号
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
void TestHufTree(HuffmanTree pHT)
{
	for (int i = 1; i < 512; ++i)
	{
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}
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
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC)
{
	////无栈非递归遍历Huffman树，求Hufffman编码
	//char cd[256] = { '\0' };	//记录访问路径
	//int cdlen = 0;				//记录当前路径长度
	//for (int i = 1; i < 512; i++)
	//{
//		pHT[i].weight = 0;		//遍历Huffman树时用节点的状态标志
//	}

	//int p = 511;//根节点
	//while (p != 0)
	//{
//		if (pHT[p].weight == 0)//向左
		//{
			//pHT[p].weight = 1;
			//if (pHT[p].lchild != 0)
			//{
//				p = pHT[p].lchild;
				//cd[cdlen++] = '0';
			//}
			//else if (pHT[p].rchild == 0)//登记叶子节点的字符的编码
			//{
				//pHC[p] = (char*)malloc((cdlen + 1)*sizeof(char));
				//cd[cdlen] = '\0';
//				strcpy(pHC[p], cd);//复制编码
			//}
		//}
//		else if (pHT[p].weight == 1)//向右
//		{
//			pHT[p].weight = 2;
//			if (pHT[p].rchild != 0)//右孩子为叶子节点
//			{
//				p = pHT[p].rchild;
//				cd[cdlen++] = '1';
//			}
//		}
//		else
//		{
//			//退回父节点，编码长度减1
//			pHT[p].weight = 0;
//			p = pHT[p].parent;
//			--cdlen;
//		}
//	}
//	return 0;
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
	if (pHT[root].lchild)//访问左孩子
		TestHufCode(pHT[root].lchild, pHT, pHC);
	if (pHT[root].rchild)//访问右孩子
		TestHufCode(pHT[root].rchild, pHT, pHC);
}