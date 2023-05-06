#include "BinarySearchTree.h"

using namespace BinarySearchTree;

Tree::Tree(){
	root = NULL;
}

Tree::~Tree(){
	delete root;
	root = NULL;
}

Node* Tree::SearchNode(int key) {
	// return NULL if empty
	if (!root)
		return NULL;
	// search from root
	if (key == root->key)
		return root;
	Node* cNode = root; // current node
	do {
		cNode = key < cNode->key
			? cNode->left    // go left if less than current node
			: cNode->right;  // go right if greater than current node
	} while (cNode && key != cNode->key);// continue if child is not NULL and not match.
	return cNode;
}

void Tree::Insert(int key, string value) {
	if (!root) {
		root = new Node(key, value);
		return;
	}
	//search insert entry
	Node* entry = root;
	Node* next = NULL;
	bool isLeft = 0; // 0 = right, 1 = left
	do {
		if (key == entry->key) // if the key is equal, return it. **Can consider inserting a sub linked list or sub tree to handle same key elements in the future.
			return;
		next = (isLeft = key < entry->key)
			? entry->left    // go left if less than current node
			: entry->right;  // go right if greater than current node
	} while (next && (entry = next));
	//start to insert new node
	Node* nNode = new Node(key, value);
	if (isLeft) {
		nNode->parent = entry;
		entry->left = nNode;
	}
	else {
		nNode->parent = entry;
		entry->right = nNode;
	}

	entry = NULL;
	next = NULL;
}

bool Tree::Remove(int key) {//return success
	if (!root)
		return false;
	// search from root
	Node* cNode = root; // current node
	if (key != cNode->key) {
		do {
			cNode = key < cNode->key
				? cNode->left    // go left if less than current node
				: cNode->right;  // go right if greater than current node
		} while (cNode && key != cNode->key);// continue if child is not NULL and not match.
	}
	if (cNode) {
		//find out the Node of near key
		Node* temp = cNode;
		if (temp->left) {
			temp = temp->left;
			while (temp->right)
				temp = temp->right;
		}
		else if (temp->right) {
			temp = temp->right;
			while (temp->left)
				temp = temp->left;
		}
		//replace removing key(*cNode) with near key(*temp)
		if (temp != cNode) {
			cNode->key = temp->key;
			cNode->value = temp->value;
		}
		// be removed from parent
		if (temp->parent) {
			if (temp->parent->left == temp) {
				if (temp->right) {
					temp->right->parent = temp->parent;
					temp->parent->left = temp->right;
				}
				else if (temp->left) {
					temp->left->parent = temp->parent;
					temp->parent->left = temp->left;
				}
				else
					temp->parent->left = NULL;
			}
			else {
				if (temp->left) {
					temp->left->parent = temp->parent;
					temp->parent->right = temp->left;
				}
				else if (temp->right) {
					temp->right->parent = temp->parent;
					temp->parent->right = temp->right;
				}
				else
					temp->parent->right = NULL;
			}
			//delete Node
			temp->left = NULL;
			temp->right = NULL;
			temp->parent = NULL;
			delete temp;
			temp = NULL;
		}
		else {
			if (root == temp)
				root = NULL;
			//delete Node
			temp->left = NULL;
			temp->right = NULL;
			temp->parent = NULL;
			delete temp;
			temp = NULL;
		}
		cNode = NULL;
		return true;
	}
	cNode = NULL;
	return false;
}
