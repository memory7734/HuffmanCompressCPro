#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<bitset>
#include "Huffman.h"
#include "Compress.h"
using namespace std;
char *pBuffer = NULL;
//��8��01�ַ�ת��Ϊһ��char
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
char* Encode(const char *pFilename, const HuffmanCode pHC,const int nSize)
{
	//���ٻ�����
	pBuffer = (char *)malloc(nSize *sizeof(char));
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
				cd[i] = cd[i + 8];
		}
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
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

int Compress(const char *pFilename)
{
	HEAD sHead;
	InitHead(pFilename, sHead);
	HTNode *pHT = (HTNode*)malloc((512) * sizeof(HTNode));
	HuffmanTreeInit(pHT, sHead.weight);
	HuffmanCode pHC = (HuffmanCode)malloc((257) * sizeof(char*));
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
	pBuffer = Encode(pFilename, pHC, nSize);
	int outlength = WriteFile(pFilename, sHead, nSize);
	cout << outlength << "�ֽ�" << endl;
	cout << "ѹ�����ʣ�" << 100.0*outlength / sHead.length << "%" << endl;
	return 0;
}
int Decompress(const char *compress_file)
{
	char decompress_file[256];
	strncpy(decompress_file, compress_file, strlen(compress_file) - 4);
	//�ض�compress_file
	decompress_file[strlen(compress_file) - 4] = '\0';
	ifstream read;
	read.open(compress_file, ios::binary);
	if (read.fail())
	{
		cout << "��ȡ�ļ�ʧ��" << endl;
		return 0;
	}
	ofstream write;
	write.open(decompress_file);
	if (write.fail())
	{
		cout << "д���ļ�ʧ��" << endl;
		return 0;
	}
	//����HEAD
	HEAD sHead;
	//��ȡ�ļ�����
	read.seekg(0, ios::end);
	//��ȡHEAD
	read.seekg(0, ios::beg);
	read.read((char*)(&sHead), sizeof(sHead));
	//��ʼ��pHT
	HTNode *pHT = (HTNode*)malloc((512) * sizeof(HTNode));
	HuffmanTreeInit(pHT, sHead.weight);
	//ָ��HEAD֮���λ��
	read.seekg(sizeof(HEAD), ios::beg);
	char next;				//��ȡ����
	int pos = 511;			//ָ��Huffman ����λ��
	read.get(next);
	unsigned long long count_size = 0;
	while (1)
	{
		bitset<8>b(next);
		read.get(next);
		for (int i = b.size() - 1; i >= 0; i--)
		{
			//�ж�b�ĵ�iλ�Ƿ�Ϊ1
			if (b.test(i))
				pos = pHT[pos].rchild;
			else
				pos = pHT[pos].lchild;
			if (pHT[pos].lchild == 0 && pHT[pos].rchild == 0)
			{
				write << pHT[pos].c;		//��ȡ�ڵ�����
				pos = 511;					//ָ��Huffman ����λ��
				++count_size;
			}
			if (count_size >= sHead.length)
				break;
		}
		if (count_size >= sHead.length)
			break;
	}
	cout << "��ѹ���" << endl;
	read.close();
	write.close();
	return 0;
}