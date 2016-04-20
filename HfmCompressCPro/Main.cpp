#include<iostream>
#include"Compress.h"
using namespace std;
//extern void HuffmanTreeInit(HuffmanTree pHT, int weight[]);
//extern void TestHufTree(HuffmanTree pHT);
int main()
{
	cout << "********Huffman文件压缩********" << endl;
	cout << "请输入文件名：";
//	char fileName[256];
//	cin >> fileName;
//	char fileName[] = "D://Setup.X64.zh-cn_O365ProPlusRetail_cc34882c-ba85-4909-9a4c-4c82d23c5cd9_TX_PR_b_48_.exe";
	char fileName[] = "D://1.txt";
	Compress(fileName);

	//显示256种字节的出现次数
	//cout << "Byte " << "Weight" << endl;
	//for (int i = 0; i < 256; i++)
	//	printf("0x%02X %d\n", i, weight[i]);
	cin >> fileName;

	return 0;
}
