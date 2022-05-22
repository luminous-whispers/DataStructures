#define _CRT_SECURE_NO_WARNINGS
//文件压缩-Huffman, 链表树实现(传统方法)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

int main()
{
	if((Src=fopen("F:\\notes\\assign\\fifth_tree\\Huffman\\data\\input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	
	statCount();
	createHTree();
	makeHCode();
	atoHZIP();

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 
void statCount()
{
	char str[500];
	int len, i;
	while (fgets(str, 500, Src) != NULL)
	{
		len = strlen(str);
		if (str[len-1]=='\n')
			str[len-1] = 0;
		for (i = 0; i < len; i++)
		{
			if (str[i]>0)
				Ccount[str[i]]++;
		}
	}
	Ccount[0]= 1;
}

//【实验步骤1】结束

//【实验步骤2】开始
int Cmp(const void *A, const void *B)
{	
	struct tnode a = * *(struct tnode **)A, 
		b = * *(struct tnode **)B;
	if (a.weight > b.weight)
		return 1;
	else if (a.weight < b.weight)
		return -1;
	else
	{
		if (a.c > b.c)
			return 1;
		else//not equal
			return -1;
	}
}
void Bubble(struct tnode **p, int len)
{
	//这里排序稳定性优点小坑, 记住只不断移动第一颗树即可
	int i;
	struct tnode *tmp;
	for (i=0; i < len-1; i++)
	{
		if ((*(p))->weight >= (*(p+1))->weight)
		{
			tmp = *(p);
			*(p) = *(p+1);
			*(p+1) = tmp;
			p++;
		}
		else 
			break;
	}
}

void createHTree()
{
	int size = 0, i, j=0;
	for (i=0; i<128; i++)
		if (Ccount[i]>0)
			size++;
	struct tnode *p;
	struct tnode ** F = 
		(struct tnode**)malloc(sizeof(struct tnode*)*size);
	for(i=0; i<128; i++)
		if(Ccount[i]>0){
			p = (struct tnode *)malloc(sizeof(struct tnode));
			p->c = i; p->weight = Ccount[i];
			p->left = p->right = NULL;
			F[j++] = p;
		}
	qsort(F, size, sizeof(struct tnode *), Cmp);
	i = 0;
	while (i < size-1)
	{
		p = (struct tnode *)malloc(sizeof(struct tnode));
		p->weight = F[i]->weight + F[i+1]->weight;
		p->left = F[i], p->right = F[i+1];
		F[++i] = p;
		Bubble(&F[i], size-i);
	}
	Root = F[size-1];
}
	

//【实验步骤2】结束

//【实验步骤3】开始

//先序遍历, 同时利用静态变量记录路径
void PreVisit(struct tnode * t)
{
	static int len = 0;
	static char str[MAXSIZE];
	//需要确保第一个传进来的不是null
	if (t->right!=NULL){
		str[len++] = '1';
		PreVisit(t->right);
		str[len++] = '0';
		PreVisit(t->left);	
		len--;
	}//注意哈夫曼树不存在度为1情况, 因此也只用判断一个指针
	else{
		str[len] = 0;
		strcpy(HCode[t->c], str);
		len--;
	}
}

void makeHCode()
{
	PreVisit(Root);
} 

//【实验步骤3】结束

//【实验步骤4】开始
void Turn2HCode(char * src, char * des)
{
	int i, j, k;
	for (i=0, j=0; src[i]!=0; i++)
	{
		for (k=0; HCode[src[i]][k]!=0; k++)
			des[j++] = HCode[src[i]][k]; 
	}
	for (k=0; HCode[0][k]!=0; k++)
			des[j++] = HCode[src[i]][k]; 
	des[j] = 0;
}

void atoHZIP()
{
	char str[500], hc, code[2000];
	int len, i;
	fclose(Src);
	Src = fopen("input.txt","r");
	while (fgets(str, 500, Src) != NULL)
	{
		len = strlen(str);
		if (str[len-1]=='\n')
			str[len-1] = 0;
	}
	//转字符串版huffman码
	Turn2HCode(str, code);

	//转字节版huffman码, 这是由于c语言只允许以byte为最小单位向文件输出
	for(i=0; code[i] != 0; i++) {
		hc = (hc << 1) | (code[i]-'0');
		if((i+1)%8 == 0) {
			fputc(hc, Obj);     //输出到目标（压缩）文件中
			printf("%x",(unsigned char)hc);   //按十六进制输出到屏幕上
		}
	}

	//处理文件结束符(0)
	if ((i+1)%8 != 1){
		for (; (i+1)%8!=1; i++)
			hc = ( hc << 1 );
		fputc(hc, Obj);
		printf("%x",(unsigned char)hc); 
	}
}

//【实验步骤4】结束

