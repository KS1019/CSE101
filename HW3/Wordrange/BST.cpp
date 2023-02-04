#include "BST.h"
#include<iostream>

BST::BST()
{
	root = NULL;
}

void BST::insert(string str)
{
	Node * to_insert = new Node(str);
	if (root)
		root = insert(root, to_insert);
	else
		root = to_insert;
}

Node* BST::insert(Node* start, Node* to_insert)
{
	if (!start)
		return to_insert;

	string key = to_insert->key;
	if (key < start->key)
		start->left = insert(start->left, to_insert);
	else if (start->key < key)
		start->right = insert(start->right, to_insert);
	else
		return start;

	start->height = 1 + max(height(start->left), height(start->right));
	start->size = size(start->left) + size(start->right);
	int balanceFactor = getBalanceFactor(start);
	if (balanceFactor > 1)
	{
		if (key < start->left->key)
		{
			return rotateRight(start);
		}
		else if (key > start->left->key)
		{
			start->left = rotateLeft(start->left);
			return rotateRight(start);
		}
	}

	if (balanceFactor < -1)
	{
		if (key > start->right->key)
		{
			return rotateLeft(start);
		}
		else if (key < start->right->key)
		{
			start->right = rotateRight(start->right);
			return rotateLeft(start);
		}
	}

	return start;
}

string BST::printInOrder()
{
	return printInOrder(root);
}

string BST::printInOrder(Node* start)
{
	if(!start) // base case
		return ""; // return empty string
	string leftpart = printInOrder(start->left);
	string rightpart = printInOrder(start->right);
  string output = "key: " + start->key + " size: " + to_string(start->size);
  if(leftpart.length() != 0) // left part is empty
  	output = leftpart + " " + output; // append left part
  if(rightpart.length() != 0) // right part in empty
    output = output + " " + rightpart; // append right part
  return output;
}

string BST::printPreOrder()
{
	return printPreOrder(root);
}

string BST :: printPreOrder(Node* start)    
{
    if(start == NULL) // base case
        return ""; // return empty string
    string leftpart = printPreOrder(start->left);
    string rightpart = printPreOrder(start->right);
  	string output = "key: " + start->key + " size: " + to_string(start->size);
    if(leftpart.length() != 0) // left part is empty
        output = output + " " + leftpart; // append left part
    if(rightpart.length() != 0) // right part in empty
        output = output + " " + rightpart; // append right part
    return output;
}

Node* BST::find(string val)
{
	return find(root, val);
}

Node* BST::find(Node* start, string val)
{
	if (!start || start->key == val) // tree is empty or we found val
        return start;
	if(val < start->key) // val is smaller, so go left
  	return find(start->left, val);
  else // val is larger, so go right
  	return find(start->right, val);
}

int BST::rangeSize(string lowerBound, string upperBound)
{
	return rangeSize(lowerBound, upperBound, root);
}

int BST::rangeSize(string lowerBound, string upperBound, Node* start)
{
	if (!start)
		return 0;
	if (lowerBound <= start->key && start->key <= upperBound)
		return rangeSize(lowerBound, upperBound, start->left) + rangeSize(lowerBound, upperBound, start->right) + 1;
	else if (start->key < lowerBound)
		return rangeSize(lowerBound, upperBound, start->right);
	else
		return rangeSize(lowerBound, upperBound, start->left);
}