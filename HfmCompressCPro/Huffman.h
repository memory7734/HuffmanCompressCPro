//Huffman 树节点
struct HTNode
{
	int weight=0;	//权值
	int parent=0;	//父节点
	int lchild=0;	//左孩子
	int rchild=0;	//右孩子
	char c;			//字符值
};
typedef HTNode *HuffmanTree;
typedef char **HuffmanCode;
void HuffmanTreeInit(HuffmanTree pHT, int weight[]);
void TestHufTree(HuffmanTree pHT);
int Select(HuffmanTree pHT, int nSize);
void TestHufTreeN(int root, HuffmanTree pHT);
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);