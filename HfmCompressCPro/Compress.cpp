#include<iostream>
#include "Huffman.h"
#include "Compress.h"
#include<stdlib.h>
using namespace std;
unsigned char *pBuffer = NULL;
unsigned char* Encode(const char *pFilename, const HuffmanCode pHC, const int nSize);
char Str2byte(const char *pBinStr);
int WriteFile(const char *pFilename, const HEAD sHead, const int nSize);
//��char��������ʾ
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
	cout << sHead.length << "�ֽ�" << endl;
	//������뻺������С
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += sHead.weight[i] * strlen(pHC[i]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	//��Դ�ļ�����ѹ������
	pBuffer= Encode(pFilename, pHC, nSize);
	int outlength = WriteFile(pFilename, sHead, nSize);
	cout<<outlength<<"�ֽ�"<<endl;
	cout << "ѹ�����ʣ�" << 100.0*outlength / sHead.length << "%" << endl;
	return 0;
}
char Str2byte(const char *pBinStr)
{
	unsigned char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;//����1λ
		if (pBinStr[i] == '1')
			b = b | 0x01;
	}
	return b;
}
unsigned char* Encode(const char *pFilename, const HuffmanCode pHC,const int nSize)
{
	unsigned char *pBuffer = NULL;
	//���ٻ�����
	pBuffer = (unsigned char *)malloc(nSize *sizeof(unsigned char));
	memset(pBuffer, 0, nSize);
	if (!pBuffer)
	{
		cerr << "���ٻ�����ʧ��" << endl;
		return NULL;
	}
	//�Զ���������ʽ���ļ�
	FILE *in = fopen(pFilename, "rb");
	char cd[5000] = { '\0' };//������
	int pos = 0;			//������ָ��
	int ch;	
	//ɨ���ļ�������Huffman�����������ѹ����ѹ������ݴ浽�������С�
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch]);//��HC���Ʊ��봮��cd
		//ѹ������
		while (strlen(cd) >= 8)
		{
			//��ȡ�ַ�����ߵ�8���ַ���������ֽ�
			pBuffer[pos++] = Str2byte(cd);
			
			//�ַ�����������8���ֽ�
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
	//��ʼ���ļ�ͷ
	strcpy(sHead.type, "HUF");//�ļ�����
	sHead.length = 0;//ԭ�ļ�����
	for (int i = 0; i < 256; i++)
	{
		sHead.weight[i] = 0;//Ȩֵ
	}
	//�Զ���������ʽ���ļ�
	FILE *in = fopen(pFilename, "rb");
	int ch;
	//ɨ���ļ����Ȩ��
	while ((ch = getc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	//�ر��ļ�
	fclose(in);
	in = NULL;
	
	return 0;
}
int WriteFile(const char *pFilename, const HEAD sHead, const int nSize)
{
	//�����ļ���
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	//�Զ���������ʽ���ļ�
	FILE *out = fopen(filename, "wb");

	//д�ļ�ͷ
	fwrite(&sHead, sizeof(HEAD), 1, out);
	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);
	//�ر��ļ����ͷ��ļ�ָ��
	fclose(out);
	out = NULL;

	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}