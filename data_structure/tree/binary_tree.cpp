#include<iostream>
using namespace std;

struct Node{
	int key;
	Node *parent, *left, *right;
};

Node *root, *NIL;

//���� 
void insert(int k){
	Node *x = root;
	Node *y = NIL;
	Node *z = new Node; 
	// Node *z = (Node *)malloc(sizeof(Node));C���Եȼ���ʽ
	z->key = k;
	z->left = NIL;
	z->right = NIL;
	
	while( x != NIL){
		y = x;
		if(z->key < x->key){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	 
	z->parent = y;
	if(y == NIL){
		root = z;
	}else{
		if(z->key < y->key){
			y->left = z;
		}else{
			y->right = z;
		}
	}
} 

//�������
void midorder(Node *u){
	if(u==NIL)
		return;
	midorder(u->left);
	cout<<" "<<u->key;
	midorder(u->right);
} 

//ǰ�����
void preorder(Node *u){
	if(u==NIL)
		return;
	cout<<" "<<u->key;
	preorder(u->left);
	preorder(u->right);
} 

//�������
void postorder(Node *u){
	if(u==NIL)
		return;
	postorder(u->left);
	postorder(u->right);
	cout<<" "<<u->key;
} 

Node *findNode(Node *u, int k){
	while(u != NIL && u->key != k){
		if(u->key < k){
			u = u->right;
		}else{
			u = u->left;
		}
	}
	return u;
}

Node *deleteNode(Node *u){
	// ���û�ж��ӣ�ֱ�Ӱ���ɾ��
	// �����һ�����ӣ��ö��Ӵ�����
	// ������������ӣ��ҵ�����û������ӵĺ��
	//�����ĺ�̱ض�û������ӣ���Ϊ��
	// 1.���ĺ�̱ض����Ҷ�����  2.������ĺ��������ӣ���ô����̵������Ӧ�ò������ĺ�̣�
	// ���ĺ������������е���һ��(��һ���Ҷ���һֱ����)
	
	Node *y = new Node; // ��ɾ���Ľڵ� 
	Node *x = new Node; // ��ɾ���Ľڵ���ӽڵ� 
	// ȷ����ɾ���Ľڵ�
	if(u -> left == NIL || u -> right == NIL){
		y = u;
	}else{// ������������ӣ���ɾ����̣����ѵ�ǰ�ڵ��ֵ��Ϊ��̵�ֵ 
		y = u -> right;
		while(y != NIL){
			y = y -> left;
		}
		y = y -> parent;
	}
	//ȷ����ɾ���Ľڵ���ӽڵ�
	if(y -> left != NIL){
		x = y -> left;
	}else{
		x = y -> right;
	}
	
	if( x != NIL ){
		x -> parent = y -> parent;
	}
	
	if( y -> parent == NIL){
		root = x;
	}else{
		if( y == y -> parent -> left){
			y -> parent -> left = x;
		}else{
			y -> parent -> right = x;
		}
	}
	//���ɾ������u�ĺ�� 
	if(y != u){
		u -> key = y -> key;
	}
	
	delete y;
}

int main(){
	for(int i=0;i<10;i++){
		insert(i);
	}
	midorder(root);
	return 0;
}
