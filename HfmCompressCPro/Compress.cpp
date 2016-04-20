#include<iostream>
#include "Huffman.h"
#include "Compress.h"
#include<stdlib.h>
using namespace std;
unsigned char *pBuffer = NULL;
unsigned char* Encode(const char *pFilename, const HuffmanCode pHC, const int nSize);
char Str2byte(const char *pBinStr);
int WriteFile(const char *pFilename, const HEAD sHead, const int nSize);
//将char二进制显示
void func(void *pBuffer, int nSize)
{
	unsigned char *pTemp = (unsigned char*)pBuffer;
	int i, j, nResult;
	int le = 0;
	for (i = nSize - 1; i >= 0; i--)
	{
		for (j = 7; j >= 0; j--)
		{
			nResult = pTemp[i] & (int)pow(2, j);
			nResult = (0 != nResult);
			cout << nResult;
			++le;
		}
	}
	cout << endl;
	cout << le;
}
int Compress(const char *pFilename)
{
	int ERROR = -1;
	HEAD sHead ;
	InitHead(pFilename, sHead);
	HTNode *pHT = (HTNode*)malloc((512)*sizeof(HTNode));
	HuffmanTreeInit(pHT, sHead.weight);
	HuffmanCode pHC = (HuffmanCode)malloc((257)*sizeof(char*));
	HuffmanCoding(pHT, pHC);
	cout << sHead.length << "字节" << endl;
	//计算编码缓冲区大小
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += sHead.weight[i] * strlen(pHC[i]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	//对源文件进行压缩编码
	pBuffer= Encode(pFilename, pHC, nSize);
	int outlength = WriteFile(pFilename, sHead, nSize);
	cout<<outlength<<"字节"<<endl;
	cout << "压缩比率：" << 100.0*outlength / sHead.length << "%" << endl;
	return 0;
}
char Str2byte(const char *pBinStr)
{
	unsigned char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;//左移1位
		if (pBinStr[i] == '1')
			b = b | 0x01;
	}
	return b;
}
unsigned char* Encode(const char *pFilename, const HuffmanCode pHC,const int nSize)
{
	unsigned char *pBuffer = NULL;
	//开辟缓冲区
	pBuffer = (unsigned char *)malloc(nSize *sizeof(unsigned char));
	memset(pBuffer, 0, nSize);
	if (!pBuffer)
	{
		cerr << "开辟缓冲区失败" << endl;
		return NULL;
	}
	//以二进制流形式打开文件
	FILE *in = fopen(pFilename, "rb");
	char cd[5000] = { '\0' };//工作区
	int pos = 0;			//缓冲区指针
	int ch;	
	//扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中。
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch]);//从HC复制编码串到cd
		//压缩编码
		while (strlen(cd) >= 8)
		{
			//截取字符串左边的8个字符，编码成字节
			pBuffer[pos++] = Str2byte(cd);
			
			//字符串整体左移8个字节
			for (int i = 0; i < 5000 - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
			
		}
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	printf("%u \n", pBuffer);
	return pBuffer;
}
int InitHead(const char *pFilename, HEAD &sHead)
{
	//初始化文件头
	strcpy(sHead.type, "HUF");//文件类型
	sHead.length = 0;//原文件长度
	for (int i = 0; i < 256; i++)
	{
		sHead.weight[i] = 0;//权值
	}
	//以二进制流形式打开文件
	FILE *in = fopen(pFilename, "rb");
	int ch;
	//扫描文件获得权重
	while ((ch = getc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	//关闭文件
	fclose(in);
	in = NULL;
	
	return 0;
}
int WriteFile(const char *pFilename, const HEAD sHead, const int nSize)
{
	//生成文件名
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	//以二进制流形式打开文件
	FILE *out = fopen(filename, "wb");

	//写文件头
	fwrite(&sHead, sizeof(HEAD), 1, out);
	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	//关闭文件，释放文件指针
	fclose(out);
	out = NULL;

	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}