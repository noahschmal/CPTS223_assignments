#include "AVLNode.h"

#ifndef __AVLTree_H
#define __AVLTree_H

#include <iostream>

using std::cout;

template <typename T>
class AVLTree {

    protected:
    // Data for root
    AVLNode<T> *root;



	// Rotate the subtree to the right
	AVLNode<T> *rightRotate(AVLNode<T> *oldRoot) {
		AVLNode<T> *newRoot = oldRoot->left;
		AVLNode<T> *subTree = newRoot->right;

		// Rotate the subtrees
		newRoot->right = oldRoot;
		oldRoot->left = subTree;

		// Update the heights of the nodes
		oldRoot->height = maximum(height(oldRoot->left), height(oldRoot->right)) + 1;
		newRoot->height = maximum(height(newRoot->left), height(newRoot->right)) + 1;

		// Return the new root
		return newRoot;
	}

	// Rotate the subtree to the left
	AVLNode<T> *leftRotate(AVLNode<T> *oldRoot)
	{
		AVLNode<T> *newRoot = oldRoot->right;
		AVLNode<T> *subTree = newRoot->left;

		// Rotate the subtrees
		newRoot->left = oldRoot;
		oldRoot->right = subTree;

		// Update the heights of the nodes
		oldRoot->height = maximum(height(oldRoot->left), height(oldRoot->right)) + 1;
		newRoot->height = maximum(height(newRoot->left), height(newRoot->right)) + 1;

		// Return the new root
		return newRoot;
	}

	// Returns the difference in height between the two child nodes
	int treeBalance(AVLNode<T> *node) {
		if (node == nullptr) {
			return 0;
		}
		return height(node->left) - height(node->right);
	}

	public:

    // Constructors
    AVLTree() {
		root = nullptr;
	}

    // Destructor
    ~AVLTree() {
            AVLDelete(this->root); 
    }

	void AVLDelete(AVLNode<T> *node)
	{
			if (node->left != nullptr) {
				AVLDelete(node->left);
			}
			if (node->right != nullptr) {
				AVLDelete(node->right);
			}
			delete (node);
	}

	// Height function
    int height() {
		return root->height;
    }

	// Inserts a node into the tree recursively
	// Returns the the root of the subtree
	AVLNode<T> *insert(AVLNode<T> *node, T data) {
		// First insert the node through a normal BST insert
		if (node == nullptr) {
			AVLNode<T> *newNode = new AVLNode<T>(data);
			return (newNode);
		}

		if (data < node->data) { // Insert to the left
			node->left = insert(node->left, data);
		}
		else if (data > node->data) { // Insert to the right
			node->right = insert(node->right, data);
		}
		else { // Equal data not allowed
			return node;
		}

		// Update the height of the node
		node->height = maximum(height(node->left), height(node->right)) + 1;

		

		// Check if the node is balanced
		int balance = treeBalance(node);

		// Balance the nodes
		
		// Left left
		if ( balance > 1 && data < node->left->data) {
			return rightRotate(node);
		}

		// Right right
		if ( balance < -1 && data > node->right->data) {
			return leftRotate(node);
		}

		// Left right
		if (balance > 1 && data < node->left->data) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// Right left
		if (balance < -1 && data < node->right->data) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	void insert(T data) {
		root = insert(root, data);
	}

	// Recursive functions for contains
	int containsHelper(AVLNode<T> *node, T search) {
		if (node == nullptr)
		{
			return 0;
		}
		else if (node->data == search) {
			return 1;
		}
		else if (node->data < search) {
			return containsHelper(node->right, search);
		}
		else if (node->data > search)
		{
			return containsHelper(node->left, search);
		}
		return 0;
	}
	// Contains
	int contains(T search) {
		AVLNode<T> *node = root;

		return containsHelper(node, search);
	}

	// Validate helper that is recursive
	int validateHelper(AVLNode<T> *node) {
		if(node != nullptr) {
			if (treeBalance(node) > 1 || treeBalance(node) < -1)
			{
				return 1;
			}
			else {
				validateHelper(node->left);
				validateHelper(node->right);
				return 0;
			}
		}
	}

	// Validate
	int validate() {
		if(validateHelper(root) == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}


	// Need this to avoid accessing the height of a null pointer
	int height(AVLNode<T> *node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			return node->height;
		}
	}

	// Returns the max of two intergers - was going to use to avoid trying to access values of null pointers
	int maximum(int x, int y)
	{
		if (x >= y)
		{
			return x;
		}
		else
		{
			return y;
		}
	}


	};
	
	

	

	

#endif