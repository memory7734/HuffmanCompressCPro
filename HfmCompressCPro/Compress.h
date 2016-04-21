struct HEAD
{
	char type[4];		//文件类型
	int length;			//原文件长度
	int weight[256];	//权值数组
};
int Compress(const char *pFilename);
int Decompress(const char *compress_file);