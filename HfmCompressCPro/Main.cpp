#include<iostream>
#include"Compress.h"
using namespace std;
//extern void HuffmanTreeInit(HuffmanTree pHT, int weight[]);
//extern void TestHufTree(HuffmanTree pHT);
int main()
{
	cout << "********Huffman�ļ�ѹ��********" << endl;
	cout << "�������ļ�����";
	char fileName[256];
	cin >> fileName;
	Compress(fileName);

	//��ʾ256���ֽڵĳ��ִ���
	//cout << "Byte " << "Weight" << endl;
	//for (int i = 0; i < 256; i++)
	//	printf("0x%02X %d\n", i, weight[i]);
	cin >> fileName;

	return 0;
}
