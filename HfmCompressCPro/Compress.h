struct HEAD
{
	char type[4];//�ļ�����
	int length;//ԭ�ļ�����
	int weight[256];//Ȩֵ����
};
int InitHead(const char *pFilename, HEAD &sHead);
int Compress(const char *pFilename);
char Str2byte(const char *pBinStr);