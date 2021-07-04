#include<iostream>
using namespace std;
#define RED 0 // define �� includeһ����������䣬ĩβ���üӷֺ�
#define BLACK 1 

struct Node{
	int key;
	char color; 
	Node *parent, *left, *right;
};

Node *root = new Node;
Node *NIL = root;

// ǰ�����
void preorder(Node *u){
	if( u == NIL ){
		return;
	}
	cout << " " << u -> key;
	preorder( u -> left );
	preorder( u -> right );
}
// �������
void midorder(Node *u){
	if( u == NIL ){
		return;
	}
	midorder( u -> left );
	cout << " " << u -> key;
	midorder( u -> right );
}
// �������
void postorder(Node *u){
	if( u == NIL ){
		return;
	}
	postorder( u -> left );
	postorder( u -> right );
	cout << " " << u -> key;
}

// �ҵ������ϵ���С�ڵ� 
Node *find_minimum(Node *z){
	while( z -> left != NIL){
		z = z -> left;
	}
	return z;
}

// ���ҽڵ�
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

// ���� 
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

// ���� 
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

// ����󣬻ָ�������ṹ 
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
				// �������ʣ���ڵ��������Ӷ��Ǻڵ� 
				z -> parent -> color = BLACK;
				z -> parent -> parent -> color = RED;
				// �������ʣ� ��һ���ڵ㿪ʼ�����м�·���Ϻڽڵ���Ŀ��ͬ 
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

// ����ڵ�
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
        cout<<" ��ǰ�ڵ㣺"<< z -> key << endl;
        cout<<" ���׵���ɫ��"<< int(z -> parent -> color)<<endl;
	rb_insert_node_fix(z);
} 


void rb_delete_node_fix(Node *x){
	Node *w = new Node;
	while( x != root && x -> color == BLACK){
		if( x == x -> parent -> left){// ������x�����ӽ�������������������Σ����ӽ����˶Գ� 
			w = x -> parent -> right; //x���ֵܽ��
			if( w -> color == RED){
				// ����һ ���ֺ� 
				w -> color = BLACK;
				x -> parent -> color = RED;
				left_rotate(x -> parent);
				w = x -> parent -> right; //ֱ�ӽ����������ζ��������� 
			}
			if( w -> left -> color == BLACK && w -> right -> color == BLACK){
				// ���ζ����յ㣩���ֺڣ������Ӻڣ������Ӻ�
				w -> color = RED;
				x = x -> parent;
			}else if( w -> right -> color == BLACK){
				// ���������ֺڣ������Ӻڣ������Ӻ�
				w -> color = RED;
				w -> left -> color = BLACK;
				right_rotate(w); 
				w = x -> parent -> right; // ֱ�ӽ������������� 
			}
			w -> color = w -> parent -> color;
			w -> parent -> color = BLACK;
			left_rotate( w -> parent );
			w -> right -> color = BLACK;
			x = root;
		}else{// ������x�����ӽ�������������������Σ����ӽ����˶Գ� 
			w = x -> parent -> left; //x���ֵܽ��
			if( w -> color == RED){
				// ����һ ���ֺ� 
				w -> color = BLACK;
				x -> parent -> color = RED;
				right_rotate(x -> parent);
				w = x -> parent -> left; //ֱ�ӽ����������ζ��������� 
			}
			if( w -> right -> color == BLACK && w -> left -> color == BLACK){
				// ���ζ����յ㣩���ֺڣ������Ӻڣ������Ӻ�
				w -> color = RED;
				x = x -> parent;
			}else if( w -> left -> color = BLACK){
				// ���������ֺڣ������Ӻڣ������Ӻ�
				w -> color = RED;
				w -> right -> color = BLACK;
				left_rotate(w); 
				w = x -> parent -> left; // ֱ�ӽ������������� 
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

// ɾ����� 
void rb_delete_node( Node *u){
	Node *y = new Node; //��ɾ���Ľڵ�
	Node *x = new Node; //��ɾ���Ľڵ���ӽڵ�
	
	// ȷ����ɾ���Ľڵ�
	if( u -> left == NIL || u -> right == NIL){
		y = u;
	}else{
		y = find_minimum(u -> right);
	}
	
	// ȷ����ɾ�������ӽ��
	if( y -> left != NIL){
		x = y -> left;
	}else{
		x = y -> right;
	}
	
	char y_original_color = y -> color;
	
	// ɾ��y 
	// �����������������ͬ�ĵط���
	//����x�ǲ���NIL������x��parent����Ϊy��parent���������Ľṹ���� 
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
	
	// ���ɾ������y�ĺ��
	if( y != u){
		u -> key = y -> key;
	} 
	
	// �ָ�������ṹ
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
