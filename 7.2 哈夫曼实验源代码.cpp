#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <malloc.h>
#define N 10
#define M 2 * N - 1

typedef struct node
{	int key;
	struct node *lchild, *rchild;
} bstnode;

int ind[9], k = 0;

typedef struct
{	char data[5]; // 结点的数据
	int weight;   // 结点的权值
	int parent;   // 结点的父结点索引
	int lchild;   // 结点的左孩子索引
	int rchild;   // 结点的右孩子索引
} HTNode;

typedef struct
{	char cd[N]; // 哈夫曼编码
	int start;  // 编码的起始位置
} HCode;


void insert(bstnode *&t, int k)
{	bstnode *p, *pre, *s;
	s = (bstnode *)malloc(sizeof(bstnode));
	s->key = k;
	s->lchild = s->rchild = NULL;
	if (t == NULL)
		t = s;
	else
	{	p = t;
		while (p != NULL)
		{	pre = p;
			if (k < p->key)
				p = p->lchild;
			else
				p = p->rchild;
		}
		if (k < pre->key)
			pre->lchild = s;
		else
			pre->rchild = s;
	}
	return;
}



void inorder(bstnode *t)//中序遍历二叉搜索树
{	if (t != NULL)
	{	inorder(t->lchild);
		ind[k] = t->key;
		k++;
		printf("%d ", t->key);
		inorder(t->rchild);
	}
}


void DispBTNode(bstnode *t)
{	if (t != NULL)
	{	printf("%d", t->key);
		if (t->lchild != NULL || t->rchild != NULL)
		{	printf("(");
			DispBTNode(t->lchild);
			if (t->rchild != NULL)
				printf(",");
			DispBTNode(t->rchild);
			printf(")");
		}
	}
}



void CreateHT(HTNode ht[], int n)// 创建哈夫曼树
{	int i, k, lnode, rnode;
	int min1, min2;
	for (i = 0; i < 2 * n - 1; i++)
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
	for (i = n; i < 2 * n - 1; i++)
	{	min1 = min2 = 32767;
		lnode = rnode = -1;
		for (k = 0; k <= i - 1; k++)
			if (ht[k].parent == -1)
			{	if (ht[k].weight < min1)
				{	min2 = min1;
					rnode = lnode;
					min1 = ht[k].weight;
					lnode = k;
				}
				else if (ht[k].weight < min2)
				{	min2 = ht[k].weight;
					rnode = k;
				}
			}
		ht[lnode].parent = i;
		ht[rnode].parent = i;
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;
		ht[i].lchild = lnode;
		ht[i].rchild = rnode;
	}
}



void CreateHCode(HTNode ht[], HCode hcd[], int n)// 创建哈夫曼编码
{	int i, f, c;
	HCode hc;
	for (i = 0; i < n; i++)
	{	hc.start = n;
		c = i;
		f = ht[i].parent;
		while (f != -1)
		{	if (ht[f].lchild == c)
				hc.cd[hc.start--] = '0';
			else
				hc.cd[hc.start--] = '1';
			c = f;
			f = ht[f].parent;
		}
		hc.start++;
		hcd[i] = hc;
	}
}


void DispHCode(HTNode ht[], HCode hcd[], int n)
{	int i, k;
	int sum = 0, j;
	printf("输出哈夫曼编码:\n");
	for (i = 0; i < n; i++)
	{	j = 0;
		printf("    %s:\t", ht[i].data);
		for (k = hcd[i].start; k <= n; k++)
		{	printf("%c", hcd[i].cd[k]);
			j++;
		}
		sum += ht[i].weight * j;
		printf("\n");
	}
	printf("\n带权路径长度=%d\n", sum);
}

int main()
{	int a[] = {23, 14, 4, 35, 68, 29, 30, 44, 100};
	int j;
	bstnode *t = NULL;
	// 构建二叉查找树
	for (j = 0; j < 9; j++)
		insert(t, a[j]);
	printf("创建的二叉树为：\n");
	DispBTNode(t);  // 输出二叉树的表示形式
	printf("\n\n");
	printf("实现中序遍历二叉树：");
	inorder(t);
	printf("\n\n");
	int n = 4, i;
	char *str[] = {"The", "of", "a", "to"};
	int fnum[] = {6, 3, 5, 10};
	HTNode ht[M];//存储哈夫曼树节点信息
	HCode hcd[N];//存储哈夫曼编码
	// 初始化哈夫曼树结点的数据和权值
	for (i = 0; i < n; i++)
	{	strcpy(ht[i].data, str[i]);
		ht[i].weight = fnum[i];
	}
	printf("\n");
	// 构建哈夫曼树
	CreateHT(ht, n);
	// 生成哈夫曼编码
	CreateHCode(ht, hcd, n);
	// 输出哈夫曼编码
	DispHCode(ht, hcd, n);

	printf("\n");
	return 0;
}