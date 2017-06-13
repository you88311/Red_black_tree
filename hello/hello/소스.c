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
	Node* Grandparent;
	Node* Uncle = NULL;

	while (  insert_node->parent != self->nillnode  && insert_node->parent->color == RED ) //�θ� ��尡 RED�� ���
	{
		Grandparent = insert_node->parent->parent;
		if (insert_node->parent == Grandparent->left) // �θ��尡 Grandparent�� left�� ���
		{
			Uncle = Grandparent->right;
			if (Uncle->color == RED) /*case 1*/    //uncle�� red�� ���
			{
				insert_node->parent->color = BLACK;
				Uncle->color = BLACK;
				Grandparent->color = RED;
				insert_node = Grandparent; //������ �� �� ��忡 ���ؼ��� while���� �ñ��
			}
			else                                       //uncle�� black�� ���
			{
				/*case2*/
				if (insert_node == insert_node->parent->right)
				{
					insert_node = insert_node->parent;
					left_rotate(insert_node, self); //case3���� ����	
				}
				/*case3*/
				insert_node->parent->color = BLACK;
				Grandparent->color = RED;
				right_rotate(Grandparent, self);
			}
		}
		else//�θ��尡 Grandparent�� right�� ���
		{
			Uncle = Grandparent->left;
			if (Uncle->color == RED) /*case 1*/
			{
				insert_node->parent->color = BLACK;
				Uncle->color = BLACK;
				Grandparent->color = RED;
				insert_node = Grandparent; //������ �� �� ���鿡 ���ؼ��� while���� �ñ��
			}
			else
			{
				/*case2*/
				if (insert_node == insert_node->parent->left)
				{
					insert_node = insert_node->parent;
					right_rotate(insert_node, self);
				}
				/*case3*/
				insert_node->parent->color = BLACK;
				Grandparent->color = RED;
				left_rotate(Grandparent, self);
			}
		}
	}
	self->root->color = BLACK; //��Ʈ�� ���� black����
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
		else
		{
			temp = temp->left;
		}
	}
	insert_node->parent = p;
	if (p == self->nillnode)
	{
		self->root = insert_node;
	}
	else if (p->value >= insert_node->value )
	{
		p->left = insert_node;
	}
	else
	{
		p->right = insert_node;
	}
	
	RB_Tree_insert_fix(insert_node, self);
}


Node* tree_minimum(Node* node, RB_Tree* self) //�־��� node���� �۰ų� ���� node ã�� �Լ�
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

		child->parent = delete_node->parent;

}

Node* tree_search(RB_Tree* self, Node* tree, int val)  //Ư������ ���� ��带 ã�� ��ȯ�ϴ� �Լ�
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
	Node*s = NULL; //sibling ���
	puts("������ ��");
	while (x != self->root && x->color == BLACK )
	{
		if (x == x->parent->left)
		{
			s = x->parent->right;
			if (s->color == RED)
			{/*case1*/
				puts("case1");
				s->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent, self);
				s = x->parent->right;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{/*case2*/
				puts("case2");
				s->color = RED;
				x = x->parent;
			}
			else if (s->left->color == RED && s->right->color == BLACK)
			{
				puts("case3");
				s->left->color = BLACK;
				s->color = RED;
				right_rotate(s, self);
				s = x->parent->right;
			}

			if (s->color==BLACK && s->right->color == RED)
			{/*case4*/
				puts("case4");
				s->color = RED;
				x->parent->color = BLACK;
				s->right->color = BLACK;
				left_rotate(x->parent, self);
				x = self->root; //��Ȳ����
			}
		}
		else
		{
			s = x->parent->left;
			if (s->color == RED)
			{/*case1*/
				puts("case5");
				s->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent, self);
				s = x->parent->left;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{/*case2*/
				puts("case6");
				s->color = RED;
				x = x->parent;
			}
			else if (s->left->color == BLACK && s->right->color == RED)
			{
				puts("case7");
				s->right->color = BLACK;
				s->color = RED;
				left_rotate(s, self);
				s = x->parent->left;
			}
			if (s->color == BLACK && s->left->color == RED)
			{
				puts("case8");
				s->color = RED;
				x->parent->color = BLACK;
				s->left->color = BLACK;
				right_rotate(x->parent, self);
				x = self->root; //��Ȳ����
			}
		}
	}
	
	x->color = BLACK;
}

void tree_delete(int data, RB_Tree* self, Node* tree)
{
	Node*delete_node = tree_search(self, tree, data); //�����ϰ� ���� ���
	Node* y = delete_node; //���� ���� Ȥ�� �̵��Ǵ� ���
	Node* x = NULL;         //y�� ���� ��ġ
	int y_original_color = delete_node->color; //y�� ���� color
	if (delete_node == self->nillnode) //������ data���� ���� ��尡 ������
		return;
	if (delete_node->left==self->nillnode && delete_node->right==self->nillnode)
	{
		x = delete_node->right;
		x->parent = delete_node->parent;
		RB_transplant(self, delete_node, x);
	}
	else if(delete_node->left == self->nillnode) //�����ʿ� child���� Ȥ�� �� �� ����
	{
		x = delete_node->right;
		RB_transplant(self, delete_node, x);
	}
	else if (delete_node->right == self->nillnode) //���ʿ� child����
	{
		x = delete_node->left;
		RB_transplant(self, delete_node, x);
	}
	else //leaf �ƴ� child�� �� ���� ���
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
		else
		{
			x->parent = y;
		}

		RB_transplant(self, delete_node, y);
		y->left = delete_node->left;
		y->left->parent = y;
		y->color = delete_node->color;
	}
	if (y_original_color == BLACK)
	{
		RB_Tree_delte_fix(x, self, self->root);
	}
	self->nillnode->parent = NULL;
}

void RB_Tree_print(RB_Tree* self, Node* tree, int level)
{
	if (tree->right != self->nillnode)
		RB_Tree_print(self, tree->right, level + 1);
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
	if (tree->left != self->nillnode)
		RB_Tree_print(self, tree->left, level + 1);
}

void left_RB_Tree_height(RB_Tree* self, Node* tree, int* left_bh)
{
	if (tree->color == BLACK)
	{
		(*left_bh) += 1;
	}
	if (tree->left != self->nillnode)
	{
		left_RB_Tree_height(self, tree->left, left_bh);
	}
	else
		return;
}
void right_RB_Tree_height(RB_Tree* self, Node* tree, int* right_bh)
{
	if (tree->color == BLACK)
	{
		(*right_bh) += 1;
	}
	if (tree->right != self->nillnode)
	{
		right_RB_Tree_height(self, tree->right, right_bh);
	}
	else
		return;
}

void RB_inorder(RB_Tree* self, Node* tree, int* total, int* bn_count)
{
	if (tree == NULL) //Ʈ�� ��ü�� ������ ����
		return;
	else {
		RB_inorder(self, tree->left, total, bn_count);
		if (tree != self->nillnode)
		{
			printf("%d ", tree->value);
			(*total) += 1; //leaf���� ��ü ��� ����
			if (tree->color == BLACK)
			{
				(*bn_count) += 1; //black_node ����
			}
		}
		RB_inorder(self, tree->right, total, bn_count);
	}
}
int main(void)
{
	int data = 0;
	int is_running = 1;
	int bn_count = 0; //number of black node
	int total = 0;
	int left_bh= 0;
	int right_bh = 0;
	RB_Tree* self = RB_Tree_alloc(); //RB_tree ����
	FILE *fp = fopen("input.txt", "r");
	while (is_running)
	{
		fscanf(fp, "%d", &data);
		if (data > 0)
		{
			
			tree_insert(node_alloc(data), self, self->root);
			left_RB_Tree_height(self, self->root, &left_bh);
			right_RB_Tree_height(self, self->root, &right_bh);
			printf("%d insert\n", data);
			if (left_bh != right_bh)
			{
				printf("insert�� �� ���� ������ bh�� ���� ����\n left_bh:%d , right_bh:%d\n", left_bh, right_bh);
				printf("insert_node:%d\n", data);
			}
			puts("---------insert�� �� Ʈ��---------");
			RB_Tree_print(self, self->root, 0);
			left_bh = 0;
			right_bh = 0;
		}
		else if (data < 0)
		{
			puts("----------delete�ϱ� �� bh�� �´� Ʈ��----------------");
			RB_Tree_print(self, self->root, 0);
			data = -data;
			printf("%d delete\n", data);
			tree_delete(data, self, self->root);
			left_RB_Tree_height(self, self->root, &left_bh);
			right_RB_Tree_height(self, self->root, &right_bh);
			if (left_bh != right_bh)
			{
				printf("delete�� �� ���� ������ bh�� ���� ����\n left_bh:%d , right_bh:%d\n", left_bh, right_bh);
				printf("delete_node:%d\n", -data);
				puts("-----------------delete�� ���� bh���� �ʴ� Ʈ��--------------");
				RB_Tree_print(self, self->root, 0);
			}
			left_bh = 0;
			right_bh = 0;

		}
		else if (data == 0)
		{
			puts("---------Red_Black tree inorder-------");
			RB_inorder(self, self->root, &total, &bn_count);
			left_RB_Tree_height(self, self->root, &left_bh);
			right_RB_Tree_height(self, self->root, &right_bh);
			puts("");
			puts("-----------------------------------");
			printf("total: %d, black_node: %d, left_bh:%d , right_bh:%d\n", total,bn_count,left_bh,right_bh);
			RB_Tree_print(self, self->root, 0);
			is_running = 0;
		}
	}
	fclose(fp);
	return 0;
}