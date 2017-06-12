#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define RED 1
#define BLACK 2

typedef struct node Node;
struct node
{
	Node* left;
	Node* right;
	Node* parent;
	int value;
	int color;
};

typedef struct rb_tree
{
	Node* root;
	Node* nillnode;
}RB_Tree;

Node* node_alloc(int val)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	new_node->value = val;
	new_node->color = RED;
	return new_node;
}

RB_Tree* RB_Tree_alloc(void)
{
	RB_Tree* tree = (RB_Tree*)malloc(sizeof(RB_Tree));
	Node* Nill_node = node_alloc(NULL);
	Nill_node->color = BLACK;
	tree->nillnode = Nill_node;
	tree->root = Nill_node;
	return tree;
}

void left_rotate(Node* node, RB_Tree* self)
{
	Node* child = node->right;
	node->right = child->left;
	if (child->left != self->nillnode )
	{
		child->left->parent = node;
	}
	child->parent = node->parent;
	if (node->parent == self->nillnode)
	{
		self->root = child;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = child;
	}
	else
	{
		node->parent->right = child;
	}
	child->left = node;
	node->parent = child;
}
void right_rotate(Node* node, RB_Tree* self)
{
	Node* child = node->left;
	node->left = child->right;
	if (child->right != self->nillnode )
	{
		child->right->parent = node;
	}
	child->parent = node->parent;
	if (node->parent == self->nillnode)
	{
		self->root = child;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = child;
	}
	else
	{
		node->parent->right = child;
	}
	child->right = node;
	node->parent = child;
}

void RB_Tree_insert_fix(Node* insert_node, RB_Tree* self)
{
	Node* Grandparent=insert_node->parent->parent;
	Node* Uncle = NULL;

	while (  insert_node->parent != self->nillnode  && insert_node->parent->color == RED ) //부모 노드가 RED인 경우
	{
		Grandparent = insert_node->parent->parent;
		if (insert_node->parent == Grandparent->left) // 부모노드가 Grandparent의 left인 경우
		{
			Uncle = Grandparent->right;
			if (Uncle->color == RED) /*case 1*/    //uncle이 red인 경우
			{
				insert_node->parent->color = BLACK;
				Uncle->color = BLACK;
				Grandparent->color = RED;
				insert_node = Grandparent; //나머지 그 위 노드에 대해서는 while문에 맡긴다
			}
			else                                       //uncle이 black인 경우
			{
				/*case2*/
				if (insert_node == insert_node->parent->right)
				{
					puts("case2");
					if (insert_node->parent->right == self->nillnode)
					{
						puts("left_rotate하는데 자식이 없는 불가능한 경우..");
					}
					left_rotate(insert_node->parent, self); //case3으로 만듬
					
				}
				/*case3*/
				insert_node->parent->color = BLACK;
				Grandparent->color = RED;
				puts("case3");
				if (Grandparent->left == self->nillnode)
				{
					puts("left_rotate하는데 자식이 없는 불가능한 경우..");
				}
				right_rotate(Grandparent, self);
			}
		}
		else if(insert_node->parent== insert_node->parent->parent->right)//부모노드가 Grand	parent의 right인 경우
		{
			Uncle = insert_node->parent->parent->left;
			if (Uncle->color == RED) /*case 1*/
			{
				insert_node->parent->color = BLACK;
				Uncle->color = BLACK;
				insert_node->parent->parent->color = RED;
				insert_node = insert_node->parent->parent; //나머지 그 위 노드들에 대해서는 while문에 맡긴다
			}
			else
			{
				/*case2*/
				if (insert_node == insert_node->parent->left)
				{
					right_rotate(insert_node->parent, self);
				}
				/*case3*/
				insert_node->parent->color = BLACK;
				insert_node->parent->parent->color = RED;
				puts("case6");
				if (insert_node->parent->parent->right == self->nillnode)
				{
					puts("이건 말이 안돼");
				}
				left_rotate(insert_node->parent->parent, self);
			}
		}


	}
	self->root->color = BLACK; //루트의 색을 black으로
}

void tree_insert(Node* insert_node, RB_Tree* self, Node* tree)
{
	Node*temp = tree;
	Node*p = self->nillnode;

	insert_node->left = self->nillnode;
	insert_node->right = self->nillnode;

	while (temp != self->nillnode)
	{
		p = temp;
		if (temp->value < insert_node->value)
		{
			temp = temp->right;
		}
		else if (temp->value > insert_node->value)
		{
			temp = temp->left;
		}
		else
			return;
	}
	insert_node->parent = p;
	if (p == self->nillnode)
	{
		self->root = insert_node;
	}
	else if (insert_node->value > p->value)
	{
		p->right = insert_node;
	}
	else
	{
		p->left = insert_node;
	}
	
	RB_Tree_insert_fix(insert_node, self);
}


Node* tree_minimum(Node* node, RB_Tree* self) //주어진 node보다 작거나 같은 node 찾는 함수
{
	if (node->left == self->nillnode)
		return node;
	else
		return tree_minimum(node->left, self);
}

void RB_transplant(RB_Tree* self, Node* delete_node, Node* child)
{
	if (delete_node->parent == self->nillnode)
	{
		self->root = child;
	}
	else if (delete_node == delete_node->parent->left)
	{
		delete_node->parent->left = child;
	}
	else
	{
		delete_node->parent->right = child;
	}
	if (child != self->nillnode)
	{
		child->parent = delete_node->parent;
	}
}

Node* tree_search(RB_Tree* self, Node* tree, int val)  //특정값을 갖는 노드를 찾아 반환하는 함수
{
	if (tree == self->nillnode || tree->value == val)
	{
		return tree;
	}
	if (tree->value < val)
	{
		return tree_search(self, tree->right, val);
	}
	else
		return tree_search(self, tree->left, val);
}
void RB_Tree_delte_fix(Node* x, RB_Tree* self, Node* tree)
{
	Node*s = NULL; //sibling 노드

	while (x != self->root && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			s = x->parent->right;
			if (s->color == RED)
			{/*case1*/
				s->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent, self);
				s = x->parent->right;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{/*case2*/
				s->color = RED;
				x = x->parent;
			}
			else if (s->left->color == RED && s->right->color == BLACK)
			{
				s->left->color = BLACK;
				s->color = RED;
				right_rotate(s, self);
				s = x->parent->right;
			}

			if (s->right->color == RED)
			{/*case4*/
				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->right->color = BLACK;
				left_rotate(x->parent, self);
				x = self->root;
			}
		}
		else if (x == x->parent->right)
		{
			s = x->parent->left;
			if (s->color == RED)
			{/*case1*/
				s->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent, self);
				s = x->parent->left;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{/*case2*/
				s->color = RED;
				x = x->parent;
			}
			else if (s->left->color == BLACK && s->right->color == RED)
			{
				s->right->color = BLACK;
				s->color = RED;
				left_rotate(s, self);
				s = x->parent->left;
			}
			if (s->left->color == RED)
			{
				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->left->color = BLACK;
				right_rotate(x->parent, self);
				x = self->root;
			}
		}
	}
	x->color = BLACK;
}

void tree_delete(int data, RB_Tree* self, Node* tree)
{
	Node*delete_node = tree_search(self, tree, data); //삭제하고 싶은 노드
	Node* y = delete_node; //삭제 혹은 이동되는 노드
	Node* x = NULL;         //y의 원래 위치
	if (delete_node == self->nillnode) //삭제할 data값을 갖는 노드가 없으면
		return;
	int y_original_color = delete_node->color; //y의 원래 color
	if (delete_node->left == self->nillnode) //오른쪽에 child있음 혹은 둘 다 없음
	{
		x = delete_node->right;
		RB_transplant(self, delete_node, x);
	}
	else if (delete_node->right == self->nillnode) //왼쪽에 child있음
	{
		x = delete_node->left;
		RB_transplant(self, delete_node, x);
	}
	else //leaf 아닌 child가 두 개인 경우
	{
		y = tree_minimum(delete_node->right, self);
		y_original_color = y->color;
		x = y->right;
		if (y->parent != delete_node)
		{
			RB_transplant(self, y, y->right);
			y->right = delete_node->right;
			y->right->parent = y;
		}

		RB_transplant(self, delete_node, y);
		y->left = delete_node->left;
		y->left->parent = y;
		y->color = delete_node->color;
	}
	if (y_original_color == BLACK)
	{
		RB_Tree_delte_fix(x, self, tree);
	}
}

void RB_Tree_print(RB_Tree* self, Node* tree, int level, int* bn_count)
{
	if (tree->right != self->nillnode)
		RB_Tree_print(self, tree->right, level + 1, bn_count);
	for (int i = 0; i < level; i++)
		printf("    ");
	if (tree->color == BLACK)
	{
		printf("%d[black]\n", tree->value);
	}
	else
	{
		printf("%d[red]\n", tree->value);
	}
	if (tree->color == BLACK)
		*bn_count += 1;
	if (tree->left != self->nillnode)
		RB_Tree_print(self, tree->left, level + 1, bn_count);
}

void RB_inorder(RB_Tree* self, Node* tree, int* total)
{
	if (tree == NULL) //트리 자체가 없으면 나옴
		return;
	else {
		RB_inorder(self, tree->left, total);
		if (tree != self->nillnode)
		{
			printf("%d ", tree->value);
		}
		(*total) += 1;
		RB_inorder(self, tree->right, total);
	}
}
int main(void)
{
	int data = 0;
	int is_running = 1;
	int nb_count = 0; //number of black node
	int total = 0;
	int black_height_level = 0;

	RB_Tree* self = RB_Tree_alloc(); //RB_tree 선언
	FILE *fp = fopen("input.txt", "r");
	while (is_running)
	{
		fscanf(fp, "%d", &data);
		if (data != 0)
		{
			tree_insert(node_alloc(data), self, self->root);
			RB_Tree_print(self, self->root, 0, &nb_count);
			puts("-----------------------------------");
		}
		else if (data == 0)
		{
			puts("Red_Black tree print!");
			RB_inorder(self, self->root, &total);
			is_running = 0;
		}
	}
	fclose(fp);
	return 0;
}