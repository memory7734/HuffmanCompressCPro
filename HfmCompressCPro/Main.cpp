#include<iostream>
#include"Compress.h"
using namespace std;
int main()
{
	int a = 1;				//��ȡ�û�ѡ��
	char file_name[256];	//��ȡ�ļ���
	while (a)
	{
		cout << "*****Huffman�ļ�ѹ��****" << endl;
		cout << "*********1.ѹ��*********" << endl;
		cout << "*********2.��ѹ*********" << endl;
		cout << "*********0.�˳�*********" << endl;
		cout << "������0~2��" ;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "��������Ҫѹ�����ļ�����";
			cin >> file_name;
			Compress(file_name);
			break;
		case 2:
			cout << "��������Ҫ��ѹ���ļ�����";
			cin >> file_name;
			Decompress(file_name);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	
	//��ʾ256���ֽڵĳ��ִ���
	//cout << "Byte " << "Weight" << endl;
	//for (int i = 0; i < 256; i++)
	//	printf("0x%02X %d\n", i, weight[i]);
	getchar();
	return 0;
}
