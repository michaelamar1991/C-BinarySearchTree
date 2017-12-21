#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
//include "malloc.h"
#include "stdlib.h"

typedef enum side { left, right } Side;

typedef struct Node
{
	int key;
	struct Node *parent, *left, *right;
} Node;

typedef struct Tree {
	Node *root;
} Tree;


//Definition of functions
void showMenu();
Tree createTree();
void insertNode(Tree *t, int key);
Node * createNode(int key, Node *parent);
void PreOrder(Node* nd);
void InOrder(Node* nd);
void PostOrder(Node* nd);
void showPress();
void Remove(Tree* bst, int value);
Node* GetSuccessor(Node* root, int value);
Node* GetNode(Node* root, int value);
int Minimum(Node* nd);
int Maximum(Node* nd);
void printLevelOrder(Node* root);
void printGivenLevel(Node* root, int level);
int height(Node* node);
void convertToPreorderDoublyLinkList(Node* node);
void printList(Node* node, int direction);

//main function
int main() {
	showMenu();

	return 0;
}

void showPress() {
	printf("\nPress any key to continue...\n");
	fflush(0);
	char c = NULL;
	c = getchar();
	c = getchar();
}

//View the menu of the program in loop.
void showMenu() {
	int choose;
	Tree t;
	int loaded = 0;
	do {
		printf("\nBinary-Search-Tree.\nPlease select your option:\n");
		printf("1. Load BST\n");
		printf("2. Insert new node\n");
		printf("3. Delete node\n");
		printf("4. Print level-order\n");
		printf("5. Print pre-order\n");
		printf("6. Print in-order\n");
		printf("7. Print post-order\n");
		printf("8. BST-Search key\n");
		printf("9. Print Tree-Minimum\n");
		printf("10. Print Tree-Maximum\n");
		printf("11. Print Tree-Successor by Key\n");
		printf("12. Convert to preorder doubly link list\n");
		printf("13. Exit\n");
		fflush(0);
		scanf("%d", &choose);
		printf("\n");

		switch (choose)
		{
			//Load tree
		case 1: {
			t = createTree();
			int arr[] = { 11, 6, 19, 4, 8, 17, 43, 5, 10, 31, 49 };
			int size = sizeof(arr) / sizeof(int);
			int i;
			for (i = 0; i < size; i++)
				insertNode(&t, arr[i]);
			printf("Tree was loaded.");
			loaded = 1;
			showPress();
			break;
		}

				//Insert new node
		case 2: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				printf("Insert new node. Please enter value:\n");
				int value;
				fflush(0);
				scanf("%d", &value);
				insertNode(&t, value);
				printf("The value %d was inserted.", value);
			}
			showPress();
			break;
		}

				//Delete node
		case 3: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				printf("Please enter value to delete: ");
				int value;
				fflush(0);
				scanf("%d", &value);
				Remove(&t, value);
				printf("The value %d was deleted.", value);
			}
			showPress();
			break;
		}

				//Print level-order
		case 4: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				printf("Print the tree in level-order:\n");
				printLevelOrder(t.root);
			}
			showPress();
			break;
		}

				//Print pre-order
		case 5: {
			if (loaded == 0)
				printf("You need to load the tree first!\n");
			else {
				printf("Print the tree in pre-order:\n");
				PreOrder(t.root);
			}
			showPress();
			break;
		}

				//Print in-order
		case 6: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				printf("Print the tree in in-order:\n");
				InOrder(t.root);
			}
			showPress();
			break;
		}

				//Print post-order
		case 7: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				printf("Print the tree in post-order\n");
				PostOrder(t.root);
			}
			showPress();
			break;
		}

				//BST-Search Key
		case 8: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				printf("Search key. Please enter value: ");
				int key;
				fflush(0);
				scanf("%d", &key);
				Node* n = GetNode(t.root, key);
				if (n == NULL)
					printf("Key was not found!");
				else
					printf("The key was found in the tree!");
			}
			showPress();
			break;
		}

				//Print Tree-Minimum
		case 9: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				int min = Minimum(t.root);
				printf("The minimum key is: %d", min);
			}
			showPress();
			break;
		}

				//Print Tree - Maximum
		case 10: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				int max = Maximum(t.root);
				printf("The maximum key is: %d", max);
			}
			showPress();
			break;
		}

				 //Print Tree-Successor by Key
		case 11: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				printf("Please enter key to get it successor: ");
				int key;
				fflush(0);
				scanf("%d", &key);
				int successor = GetSuccessor(t.root, key)->key;
				printf("The successor of %d is %d", key, successor);
			}
			showPress();
			break;
		}

				 //Convert to preorder doubly link list
		case 12: {
			if (loaded == 0)
				printf("You need to load the tree first!");
			else {
				convertToPreorderDoublyLinkList(t.root);
				printf("The tree was converted to doubly linked list in pre-order:\n");
				printList(t.root, 0);
				loaded = 0;
			}
			showPress();
			break;
		}

		default:
			break;
		}
	} while (choose != 13);
}

//Create new tree
Tree createTree() {
	Tree t;
	t.root = NULL;
	return t;
}

//Insert new node to the tree
void insertNode(Tree *t, int key) {
	Node *parent = NULL;
	Node *current = t->root;

	while (current != NULL) {
		parent = current;
		if (key <= current->key)
			current = current->left;
		else
			current = current->right;
	}

	Node *New_nd = createNode(key, parent);

	if (parent == NULL)
		t->root = New_nd;
	else {
		if (key < parent->key)
			parent->left = New_nd;
		else
			parent->right = New_nd;
	}
}

//Create new node and allocate memory
Node * createNode(int key, Node *parent) {
	Node *n = (Node*)malloc(sizeof(Node));
	n->key = key;
	n->parent = parent;
	n->left = NULL;
	n->right = NULL;
	return n;
}

//Print the tree in pre-order
void PreOrder(Node* nd) {
	if (nd == NULL)
		return;
	printf("%d, ", nd->key);
	PreOrder(nd->left);
	PreOrder(nd->right);
}

//Print BST in IN-Oreder
void InOrder(Node* nd) {
	if (nd == NULL)
		return;
	if (nd->left != NULL)
		InOrder(nd->left);
	printf("%d, ", nd->key);
	if (nd->right != NULL)
		InOrder(nd->right);
}

//Print BST in Post-Oreder
void PostOrder(Node* nd) {
	if (nd == NULL)
		return;
	PostOrder(nd->left);
	PostOrder(nd->right);
	printf("%d, ", nd->key);
}

//Remove Node from BST
void Remove(Tree* bst, int value) {
	Node* root = bst->root;
	Node* nd = GetNode(root, value);
	Node* parent = nd->parent;
	Side side;
	if (parent != NULL) {
		if (parent->left == nd)
			side = left;
		else
			side = right;
	}
	else
		side = left;

	if (nd->left == NULL && nd->right == NULL) { //In case node is a leaf
		if (side == left)
			parent->left = NULL;
		else
			parent->right = NULL;
		free(nd);
	}

	else if (nd->left == NULL && nd->right != NULL) { //In case node have only right child
		if (side == left)
			parent->left = nd->right;
		else
			parent->right = nd->right;
	}

	else if (nd->left != NULL && nd->right == NULL) { //In case node have only left child
		if (side == left)
			parent->left = nd->left;
		else
			parent->right = nd->left;
	}

	else if (nd->left != NULL && nd->right != NULL) { //In case node have 2 childs
		Node* successor = GetSuccessor(root, value);
		nd->key = successor->key;
		successor->key = value;
		parent = successor->parent;
		if (parent->right == successor)
			parent->right = successor->right;
		else
			parent->left = successor->right;
		free(successor);
	}
}

//Return node by value
Node* GetNode(Node* root, int value) {
	if (root == NULL)
		return NULL;
	else if (root->key == value)
		return root;
	else {
		if (root->key > value)
			return GetNode(root->left, value);
		else
			return GetNode(root->right, value);
	}
}

//return successor of a node.
Node* GetSuccessor(Node* root, int value) {
	Node* nd = GetNode(root, value);
	if (nd->right != NULL)
		return GetNode(root, Minimum(nd->right));
	Node* parent = nd->parent;
	while (parent != NULL && nd == parent->right) {
		nd = parent;
		parent = nd->parent;
	}
	return parent;
}

//Return minimum value of BST
int Minimum(Node* nd) {
	while (nd->left != NULL)
		nd = nd->left;
	return nd->key;
}

//Return maximum value of BST
int Maximum(Node* nd) {
	while (nd->right != NULL)
		nd = nd->right;
	return nd->key;
}

//Print the tree in level order
void printLevelOrder(Node* root)
{
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
		printGivenLevel(root, i);
}

//Print nodes at a given level
void printGivenLevel(Node* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		printf("%d ", root->key);
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}

//Compute the "height" of a tree
int height(Node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		/* compute the height of each subtree */
		int lheight = height(node->left);
		int rheight = height(node->right);

		/* use the larger one */
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

//Cov
void convertToPreorderDoublyLinkList(Node* node) {
	if (node == NULL)
		return;

	int last = 1;

	//First go to the last right child
	if (node->right != NULL){
		convertToPreorderDoublyLinkList(node->right);
		last = 0;
	}
	
	if (node->left != NULL){
		convertToPreorderDoublyLinkList(node->left);
		last = 0;
	}

	if (node->parent != NULL) {
		//if the node is right child
		if (node->parent->right == node) {
			//if the node don't have left brother
			if (node->parent->left == NULL){
				node->left = node->parent;
			}
			//if the node have left brother
			else {
				Node *leftBrother = node->parent->left;
				//go to the last right chil`d of the left brother
				while (leftBrother->right != NULL)
					leftBrother = leftBrother->right;
				node->left = leftBrother;
			}
		}

		//if the node is left child.
		if (node->parent->left == node){
			node->left = node->parent;
		}
	}
	else {
			node->left = NULL;
			Node *current = node;
			while (current->right != NULL)
				current = current->right;

			while (current->left != NULL) {
				current->left->right = current;
				current = current->left;
			}
	}
}

//print the linked list. direction 0 = left to right, 1 = right to left.
void printList(Node* node, int direction) {
	if (node == NULL)
		return;
	Node *current = node;

	if (direction == 0) {
		do {
			printf("%d ", current->key);
			current = current->right;
		} while (current != NULL);
	}

	else if (direction == 1) {
		while (current->right != NULL)
			current = current->right;
		while (current != NULL) {
			printf("%d, ", current->key);
			current = current->left;
		}
	}
}
