#include <iostream>
using namespace std;

typedef struct Node {
	int key;
	Node *lchild;
	Node *rchild;
	int high;
}BTNode;
//取最大值
int max(int a, int b) {
	return a > b ? a : b;
}
//取节点高度
int high(BTNode *q) {
	if (q == NULL)
		return 0;
	else
		return q->high;
}
//进行ll旋转
BTNode *ll_rotate(BTNode *&q) {
	BTNode *p = q->lchild;
	q->lchild = p->rchild;
	p->rchild = q;

	q->high = max(high(q->lchild), high(q->rchild)) + 1;
	p->high = max(high(p->lchild), high(p->rchild)) + 1;

	return p;
}
//进行rr旋转
BTNode *rr_rotate(BTNode *&q) {
	BTNode *p = q->rchild;
	q->rchild = p->lchild;
	p->lchild = q;

	q->high = max(high(q->lchild), high(q->rchild)) + 1;
	p->high = max(high(p->lchild), high(p->rchild)) + 1;

	return p;
}
//进行lr旋转
BTNode *lr_rotate(BTNode *&q) {
	q->lchild=rr_rotate(q->lchild);
	return ll_rotate(q);
}
//进行rl旋转
BTNode *rl_rotate(BTNode *&q) {
	q->lchild=ll_rotate(q->rchild);
	return rr_rotate(q);
}
//计算平衡因子
int getBalance(BTNode *n) {
	if (n == NULL)
		return 0;
	return high(n->lchild) - high(n->rchild);
}
//插入节点
 bool insert(BTNode *&node, int key) {
	if (node == NULL) {
		node = new BTNode;
		node->key = key;
		node->lchild = NULL;
		node->rchild = NULL;
		node->high = 1;
		return true;
	}
	if (key < node->key)
		insert(node->lchild, key);
	else if (key > node->key)
		insert(node->rchild, key);
	else 
		return false;

	node->high = max(high(node->lchild), high(node->rchild)) + 1;

	int balance = getBalance(node);

	if (balance > 1 && key < node->lchild->key)
		node=ll_rotate(node);
	else if (balance< -1 && key>node->rchild->key)
		node=rr_rotate(node);
	else if (balance > 1 && key > node->lchild->key)
		node=lr_rotate(node);
	else if (balance < -1 && key < node->rchild->key)
		node=rl_rotate(node);

	return true;
}
 //输出二叉树
 void print(BTNode *bt) {
	 if (bt != NULL) {
		 cout << bt->key;
		 if (bt->lchild != NULL || bt->rchild != NULL) {
			 cout << "(";
			 print(bt->lchild);
			 if (bt->rchild != NULL) cout << ",";
			 print(bt->rchild);
			 cout << ")";
		 }
	 }
 }
 //创建平衡二叉树
void create(BTNode *&bt, int ch[], int n) {
	bt = new BTNode;
	bt = NULL;
	for (int i = 0; i < n; i++)
	{
		insert(bt, ch[i]);
		print(bt);
		cout << endl;
	}
}

BTNode *minValueNode(BTNode *node) {
	BTNode *current = node;
	while (current->lchild != NULL)
		current = current->lchild;

	return current;
}

bool deleteNode(BTNode *&bt, int key) {
	if (bt == NULL)
		return false;
	if (key < bt->key)
		deleteNode(bt->lchild, key);
	else if (key > bt->key)
		deleteNode(bt->rchild, key);
	else {
		if ((bt->lchild == NULL) || (bt->rchild == NULL)) {
			BTNode *temp = bt->lchild ? bt->lchild : bt->rchild;
			if (temp == NULL)
				bt = NULL;
			else
				*bt = *temp;
			delete temp;
		}
		else {
			BTNode *temp = minValueNode(bt->rchild);
			bt->key = temp->key;
			deleteNode(bt->rchild, temp->key);
		}
	}

	if (bt == NULL)
		return true;
	bt->high = max(high(bt->lchild), high(bt->rchild)) + 1;

	int balance = getBalance(bt);

	if (balance > 1 && key < bt->lchild->key)
		bt = ll_rotate(bt);
	else if (balance< -1 && key>bt->rchild->key)
		bt = rr_rotate(bt);
	else if (balance > 1 && key > bt->lchild->key)
		bt = lr_rotate(bt);
	else if (balance < -1 && key < bt->rchild->key)
		bt = rl_rotate(bt);

	return true;
}

int main() {
	BTNode *bt;
	int ch[] = { 9,5,10,0,6,11,-1,1,2 };
	create(bt, ch, 9);
	deleteNode(bt, 1);
	print(bt);

	system("pause");
	return 0;
}