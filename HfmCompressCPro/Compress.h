struct HEAD
{
	char type[4];		//�ļ�����
	int length;			//ԭ�ļ�����
	int weight[256];	//Ȩֵ����
};
int Compress(const char *pFilename);
int Decompress(const char *compress_file);