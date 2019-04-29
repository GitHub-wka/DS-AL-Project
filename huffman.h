struct HTNode
{
	char n;
	int weight;
	int parent;
	int lchild;
	int rchild;
	char code[256] = {'\0'};
};
typedef HTNode *HuffmanTree;
HuffmanTree creat(int * w, int n);
void creat_code(HuffmanTree H, int n);
int chose_min(HuffmanTree HT, int m);