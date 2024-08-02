#ifndef algo_tree_h
#define algo_tree_h

#include "data.h"
#include "memory.h"



typedef struct Node{
	Value value;
	struct Node *left;
	struct Node *right;
}TreeNode;

void show_tree();
#endif
