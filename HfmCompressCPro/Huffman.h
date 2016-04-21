//Huffman ���ڵ�
struct HTNode
{
	int weight=0;	//Ȩֵ
	int parent=0;	//���ڵ�
	int lchild=0;	//����
	int rchild=0;	//�Һ���
	char c;			//�ַ�ֵ
};
typedef HTNode *HuffmanTree;
typedef char **HuffmanCode;
void HuffmanTreeInit(HuffmanTree pHT, int weight[]);
void TestHufTree(HuffmanTree pHT);
int Select(HuffmanTree pHT, int nSize);
void TestHufTreeN(int root, HuffmanTree pHT);
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);