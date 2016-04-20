#include<iostream>
#include"Compress.h"
using namespace std;
//extern void HuffmanTreeInit(HuffmanTree pHT, int weight[]);
//extern void TestHufTree(HuffmanTree pHT);
int main()
{
	cout << "********Huffman文件压缩********" << endl;
	cout << "请输入文件名：";
	char fileName[256];
	cin >> fileName;
	Compress(fileName);

	//显示256种字节的出现次数
	//cout << "Byte " << "Weight" << endl;
	//for (int i = 0; i < 256; i++)
	//	printf("0x%02X %d\n", i, weight[i]);
	cin >> fileName;

	return 0;
}
