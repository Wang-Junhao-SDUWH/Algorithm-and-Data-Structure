#include<iostream>
using namespace std;

struct Node{
	int key;
	Node *parent, *left, *right;
};

Node *root, *NIL;

//插入 
void insert(int k){
	Node *x = root;
	Node *y = NIL;
	Node *z = new Node; 
	// Node *z = (Node *)malloc(sizeof(Node));C语言等价形式
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

//中序遍历
void midorder(Node *u){
	if(u==NIL)
		return;
	midorder(u->left);
	cout<<" "<<u->key;
	midorder(u->right);
} 

//前序遍历
void preorder(Node *u){
	if(u==NIL)
		return;
	cout<<" "<<u->key;
	preorder(u->left);
	preorder(u->right);
} 

//后序遍历
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
	// 如果没有儿子，直接把他删除
	// 如果有一个儿子，拿儿子代替他
	// 如果有两个儿子，找到他的没有左儿子的后继
	//（他的后继必定没有左儿子，因为：
	// 1.它的后继必定在右儿子中  2.如果他的后继有左儿子，那么他后继的左儿子应该才是他的后继）
	// 他的后继是中序遍历中的下一个(第一个右儿子一直向左)
	
	Node *y = new Node; // 待删除的节点 
	Node *x = new Node; // 待删除的节点的子节点 
	// 确定待删除的节点
	if(u -> left == NIL || u -> right == NIL){
		y = u;
	}else{// 如果有两个儿子，则删除后继，并把当前节点的值改为后继的值 
		y = u -> right;
		while(y != NIL){
			y = y -> left;
		}
		y = y -> parent;
	}
	//确定待删除的节点的子节点
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
	//如果删除的是u的后继 
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
