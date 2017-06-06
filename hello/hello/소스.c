#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 2

typedef struct node
{
	Node* left;
	Node* right;
	Node* parent;
	int value;
	int color;
}Node;

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

typedef struct rb_tree
{
	Node* root;
}RB_Tree;

RB_Tree* RB_Tree_alloc(void)
{
	RB_Tree* tree = (RB_Tree*)malloc(sizeof(RB_Tree));
	tree->root = NULL;
	return tree;
}

void tree_insert(Node* insert_node, RB_Tree* self, Node* tree)
{

	if (self->root = NULL) //Root�� ����ִ� ���
	{
		self->root = insert_node;
		insert_node->color = BLACK;
	}
	else if (insert_node->value <tree->value) //���� ��庸�� ���� ���
	{
		if (tree->left == NULL)
		{
			tree->left = insert_node;
			insert_node->parent = tree;
		}
		else
			tree_insert(insert_node, self, tree->left);
	}
	else                      //���� ��庸�� ū ���
	{
		if (tree->right == NULL)
		{
			tree->right = insert_node;
			insert_node->parent = tree;
		}
		else
			tree_insert(insert_node, self, tree->right);
	}
	void RB_Tree_insert_fix(insert_node, self, tree);
}

void RB_Tree_insert_fix(Node* insert_node, RB_Tree* self, Node* tree)
{
	if (insert_node->parent->color == BLACK) /*�θ��� color�� BLACK�� ���*/
		return;
	else /*�θ��� color�� RED�� ���*/
	{

	}
}
int main(void)
{
	int index = 0;
	int data = 0;
	int is_running = 1;
	RB_Tree* tree = RB_Tree_alloc(); //RB_tree ����

	while (is_running)
	{
		FILE *fp = fopen("input.txt", "r");
		fscanf(fp, "%d", &data);
		if (data > 0)
		{

		}
		else if (data < 0)
		{

		}
		else if (data == 0)
		{

			is_running = 0;
		}
	}
	return 0;
}