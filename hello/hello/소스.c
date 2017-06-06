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
	tree->root = NULL;
	return tree;
}
void left_rotate( Node* node, RB_Tree* self)
{
	Node* child = node->right;
	node->right = child->left;
	if (child->left != NULL)
	{
		child->left->parent = node;
	}
	child->parent = node->parent;
	if (node->parent == NULL)
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
	if (child->right != NULL)
	{
		child->right->parent = node;
	}
	child->parent = node->parent;
	if (node->parent == NULL)
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
void tree_insert(Node* insert_node, RB_Tree* self, Node* tree)
{

	if (self->root = NULL) //Root가 비어있는 경우
	{
		self->root = insert_node;
		insert_node->color = BLACK;
	}
	else if (insert_node->value <tree->value) //현재 노드보다 작은 경우
	{
		if (tree->left == NULL)
		{
			tree->left = insert_node;
			insert_node->parent = tree;
		}
		else
			tree_insert(insert_node, self, tree->left);
	}
	else                      //현재 노드보다 큰 경우
	{
		if (tree->right == NULL)
		{
			tree->right = insert_node;
			insert_node->parent = tree;
		}
		else
			tree_insert(insert_node, self, tree->right);
	}
	void RB_Tree_insert_fix(insert_node, self);
}

void RB_Tree_insert_fix(Node* insert_node, RB_Tree* self)
{
	Node* Grandparent = insert_node->parent->parent;
	Node* Uncle = NULL;

	while (insert_node->parent->color == RED) //부모 노드가 RED인 경우
	{
		Grandparent = insert_node->parent->parent;
		if (insert_node->parent == Grandparent->left) // 부모노드가 Grandparent의 left인 경우
		{
			Uncle = Grandparent->right;
			if (Uncle->color == RED) /*case 1*/
			{
				insert_node->parent = BLACK;
				Uncle->color = BLACK;
				Grandparent = RED;
				insert_node = Grandparent; //나머지 그 위 노드에 대해서는 while문에 맡긴다
			}
			else
			{
				/*case2*/
				if (insert_node = insert_node->parent->right)
				{
					left_rotate(insert_node->parent,self);
				}
				/*case3*/
				insert_node->parent = BLACK;
				Grandparent->color = RED;
				right_rotate(Grandparent, self);
			}
		}
		else //부모노드가 Grand	parent의 right인 경우
		{
			Uncle = Grandparent->left;
			if (Uncle->color == RED) /*case 1*/
			{
				insert_node->parent = BLACK;
				Uncle->color = BLACK;
				Grandparent = RED;
				insert_node = Grandparent; //나머지 그 위 노드들에 대해서는 while문에 맡긴다
			}
			else
			{
				/*case2*/
				if (insert_node = insert_node->parent->left)
				{
					right_rotate(insert_node->parent, self);
				}
				/*case3*/
				insert_node->parent = BLACK;
				Grandparent->color = RED;
				left_rotate(Grandparent, self);
			}
		}
	}
	self->root = BLACK;
}

void tree_delete(Node* delete_node, RB_Tree* self, Node* tree)
{

}
void RB_Tree_delte_fix(Node* delte_node, RB_Tree* self, Node* tree)
{

}

int main(void)
{
	int index = 0;
	int data = 0;
	int is_running = 1;
	RB_Tree* tree = RB_Tree_alloc(); //RB_tree 선언

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