#include<iostream>
#include"Compress.h"
using namespace std;
int main()
{
	int a = 1;				//获取用户选择
	char file_name[256];	//获取文件名
	while (a)
	{
		cout << "*****Huffman文件压缩****" << endl;
		cout << "*********1.压缩*********" << endl;
		cout << "*********2.解压*********" << endl;
		cout << "*********0.退出*********" << endl;
		cout << "请输入0~2：" ;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "请输入需要压缩的文件名：";
			cin >> file_name;
			Compress(file_name);
			break;
		case 2:
			cout << "请输入需要解压的文件名：";
			cin >> file_name;
			Decompress(file_name);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	
	//显示256种字节的出现次数
	//cout << "Byte " << "Weight" << endl;
	//for (int i = 0; i < 256; i++)
	//	printf("0x%02X %d\n", i, weight[i]);
	getchar();
	return 0;
}
