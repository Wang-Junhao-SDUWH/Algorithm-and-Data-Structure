#include<iostream>
using namespace std;
#define RED 0 // define 和 include一样，不是语句，末尾不用加分号
#define BLACK 1 

struct Node{
	int key;
	char color; 
	Node *parent, *left, *right;
};

Node *root = new Node;
Node *NIL = root;

// 前序遍历
void preorder(Node *u){
	if( u == NIL ){
		return;
	}
	cout << " " << u -> key;
	preorder( u -> left );
	preorder( u -> right );
}
// 中序遍历
void midorder(Node *u){
	if( u == NIL ){
		return;
	}
	midorder( u -> left );
	cout << " " << u -> key;
	midorder( u -> right );
}
// 后序遍历
void postorder(Node *u){
	if( u == NIL ){
		return;
	}
	postorder( u -> left );
	postorder( u -> right );
	cout << " " << u -> key;
}

// 找到子树上的最小节点 
Node *find_minimum(Node *z){
	while( z -> left != NIL){
		z = z -> left;
	}
	return z;
}

// 查找节点
Node *find_node(Node *u, int k){
	while(u != NIL && u->key != k){
		if(u->key < k){
			u = u->right;
		}else{
			u = u->left;
		}
	}
	return u;
}

// 左旋 
void left_rotate( Node *x ){
	Node *y = x -> right;
	
	x -> right = y -> left;
	if( y -> left != NIL ){
		y -> left -> parent = x;
	}
	
	y -> parent = x -> parent;
	if( x -> parent == NIL){
		root = y;
	}else if( x == x-> parent -> left){
		x -> parent -> left = y;
	}else{
		x -> parent -> right = y;
	}
	
	y -> left = x;
	x -> parent = y;
}

// 右旋 
void right_rotate( Node *x ){
	Node *y = x -> left;
	
	x -> left = y -> right; 
	if( y -> right != NIL){
		y -> right -> parent = x;
	}
	
	y -> parent = x -> parent;
	if( x -> parent == NIL){
		root = y;
	}else if( x == x -> parent -> left){
		x -> parent -> left = y;
	}else{
		x -> parent -> right = y;
	}
	
	x -> parent = y;
	y -> right = x;
}

// 插入后，恢复红黑树结构 
void rb_insert_node_fix(Node *z){
	Node *y = new Node;
	while(z -> parent -> color == RED){
		if( z -> parent == z -> parent -> parent -> left){
			y = z -> parent -> parent -> right;
			if( y -> color == RED){ // case 1
				z -> parent -> color = BLACK;
				y -> color = BLACK;
				z -> parent -> parent -> color = RED;
				z = z -> parent -> parent;
			}else if( z == z -> parent -> right){ // case 2
				z = z -> parent;
				left_rotate( z);
			}else{ // case 3
				// 保持性质：红节点两个儿子都是黑的 
				z -> parent -> color = BLACK;
				z -> parent -> parent -> color = RED;
				// 保持性质： 从一个节点开始的所有简单路径上黑节点数目相同 
				right_rotate(z -> parent -> parent);
			}
		}else{
			y = z -> parent -> parent -> left;
			if( y -> color == RED){ // case 1
				z -> parent -> color = BLACK;
				y -> color = BLACK;
				z -> parent -> parent -> color = RED;
				z = z -> parent -> parent;
			}else if( z == z -> parent -> left){ // case 2
				z = z -> parent;
				right_rotate( z);
			}else{ //case 3
				z -> parent -> color = BLACK;
				z -> parent -> parent -> color = RED;
				left_rotate(z -> parent -> parent);
			}
		}
	}
	root -> color = BLACK;
}

// 插入节点
void rb_insert_node( int k ){
	Node *y = NIL;
	Node *x = root;
	Node *z = new Node;
	z -> left = NIL;
	z -> right = NIL;
	z -> key = k;
	z -> color = RED;
	
	while( x != NIL){
		y = x;
		if( k < x -> key){
			x = x -> left;
		}else{
			x = x -> right;
		}
	}
	
	z -> parent = y;
	if( y == NIL ){
		root = z;
	}else{
		if( z -> key < y -> key ){
			y -> left = z;
		}else{
			y -> right = z;
		}
	}
        cout<<" 当前节点："<< z -> key << endl;
        cout<<" 父亲的颜色："<< int(z -> parent -> color)<<endl;
	rb_insert_node_fix(z);
} 


void rb_delete_node_fix(Node *x){
	Node *w = new Node;
	while( x != root && x -> color == BLACK){
		if( x == x -> parent -> left){// 首先在x是左子结点的情况下讨论四种情形，右子结点与此对称 
			w = x -> parent -> right; //x的兄弟结点
			if( w -> color == RED){
				// 情形一 ，兄红 
				w -> color = BLACK;
				x -> parent -> color = RED;
				left_rotate(x -> parent);
				w = x -> parent -> right; //直接进入后面的情形二、三、四 
			}
			if( w -> left -> color == BLACK && w -> right -> color == BLACK){
				// 情形二（终点），兄黑，兄右子黑，兄左子黑
				w -> color = RED;
				x = x -> parent;
			}else if( w -> right -> color == BLACK){
				// 情形三，兄黑，兄右子黑，兄左子红
				w -> color = RED;
				w -> left -> color = BLACK;
				right_rotate(w); 
				w = x -> parent -> right; // 直接进入后面的情形四 
			}
			w -> color = w -> parent -> color;
			w -> parent -> color = BLACK;
			left_rotate( w -> parent );
			w -> right -> color = BLACK;
			x = root;
		}else{// 首先在x是左子结点的情况下讨论四种情形，右子结点与此对称 
			w = x -> parent -> left; //x的兄弟结点
			if( w -> color == RED){
				// 情形一 ，兄红 
				w -> color = BLACK;
				x -> parent -> color = RED;
				right_rotate(x -> parent);
				w = x -> parent -> left; //直接进入后面的情形二、三、四 
			}
			if( w -> right -> color == BLACK && w -> left -> color == BLACK){
				// 情形二（终点），兄黑，兄右子黑，兄左子黑
				w -> color = RED;
				x = x -> parent;
			}else if( w -> left -> color = BLACK){
				// 情形三，兄黑，兄右子黑，兄左子红
				w -> color = RED;
				w -> right -> color = BLACK;
				left_rotate(w); 
				w = x -> parent -> left; // 直接进入后面的情形四 
			}
			w -> color = w -> parent -> color;
			w -> parent -> color = BLACK;
			right_rotate( w -> parent );
			w -> left -> color = BLACK;
			x = root;
		}
	}
	x -> color = BLACK;
}

// 删除结点 
void rb_delete_node( Node *u){
	Node *y = new Node; //待删除的节点
	Node *x = new Node; //待删除的节点的子节点
	
	// 确定待删除的节点
	if( u -> left == NIL || u -> right == NIL){
		y = u;
	}else{
		y = find_minimum(u -> right);
	}
	
	// 确定待删除结点的子结点
	if( y -> left != NIL){
		x = y -> left;
	}else{
		x = y -> right;
	}
	
	char y_original_color = y -> color;
	
	// 删除y 
	// 这是与二叉搜索树不同的地方：
	//无论x是不是NIL，都把x的parent设置为y的parent，方便后面的结构调整 
	x -> parent = y -> parent;
	
	if( y -> parent == NIL){
		root = x;
	}else{
		if( y == y -> parent -> left){
			y -> parent -> left = x;
		}else{
			y -> parent -> right = x; 
		}
	}
	
	// 如果删除的是y的后继
	if( y != u){
		u -> key = y -> key;
	} 
	
	// 恢复红黑树结构
	if( y_original_color == BLACK){
		rb_delete_node_fix(x);
	}
} 


int main(){
	NIL -> color = BLACK;
	int test[5] = { 1, 3, 2, 4, 1};	
	for( int i = 0; i < sizeof(test) / sizeof(test[0]); i++){
		rb_insert_node(test[i]);
	}
	preorder(root);
	cout<<endl;
	rb_delete_node(find_node(root, 1));
	rb_delete_node(find_node(root, 5));
	rb_delete_node(find_node(root, 3));
	preorder(root);
	cout<<endl;
	return 0;
}
