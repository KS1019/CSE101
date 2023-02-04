#include <string>
#include <iostream>

using namespace std;

class Node
{
	public:
		int height;
		int size; // subtree sizes
		string key;
		Node *left, *right, *parent;

		Node()
		{
			left = right = parent = NULL;
			height = 1;
			size = 1;
		};

		Node(string val)
		{
			key = val;
			left = right = parent = NULL;
			height = 1;
			size = 1;
		};
};

inline int max(int lhs, int rhs)
{
	if (lhs > rhs)
		return lhs;
	else
		return rhs;
}

inline int height(Node* node)
{
	if (node)
		return node->height;
	else
		return 0;
}

inline int size(Node* node)
{
	if (node)
		return node->size;
	else
		return 0;
}

inline Node* rotateRight(Node* y)
{
	Node* x = y->left;
	Node* t2 = x->right;

	int ysize = size(y) - size(x->left);
	int xsize = size(x) + size(y->right);
	x->right = y;
	y->left = t2;
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	x->size = xsize;
	y->size = ysize;

	return x;
}

inline Node* rotateLeft(Node* x)
{
	Node* y = x->right;
	Node* t2 = y->left;

	int xsize = size(x) - size(y->right);
	int ysize = size(y) + size(x->left);

	y->left = x;
	x->right = t2;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1; 

	x->size = xsize;
	y->size = ysize;

	return y;
}

inline int getBalanceFactor(Node* node)
{
	if (node)
		return height(node->left) - height(node->right);
	else
		return 0;
}

class BST
{
	private:
		Node* root;
	public:
		BST();
		void insert(string str);
		// void insert(Node* start, Node* to_insert);
		Node* insert(Node* start, Node* to_insert);
		Node* find(string key);
		Node* find(Node* start, string key);
		string printInOrder();
		string printInOrder(Node*);
		string printPreOrder();
		string printPreOrder(Node*);
		int rangeSize(string lowerBound, string upperBound);
		int rangeSize(string lowerBound, string upperBound, Node* start);
		// void rangeSize(string lowerBound, string upperBound, Node* start, int* size);
};