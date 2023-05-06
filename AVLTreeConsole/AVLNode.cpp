#include "BinarySearchTree.h"

using namespace BinarySearchTree;

AVLNode::AVLNode(int key) : Node::Node(key){
	//initialize node status
	height = 1;
	parent = NULL;
	left = NULL;
	right = NULL;
}


AVLNode::AVLNode(int key, string value) : Node::Node(key, value){
	//initialize node status
	height = 1;
	parent = NULL;
	left = NULL;
	right = NULL;
}

AVLNode::~AVLNode() {
	delete left;
	delete right;

	parent = NULL;
	left = NULL;
	right = NULL;
}

int AVLNode::LeftCompareRight() { // return difference of left and right, return +N = L > R; return 0 = L = R; return -N = L < R;
	return (left ? left->height : 0) - (right ? right->height : 0);
}

void AVLNode::UpdateHeight() {
	if (left && right) {
		if (left->height > right->height)
			height = 1 + left->height;
		else
			height = 1 + right->height;
	}
	else if (left) { // && !right
		height = 1 + left->height;
	}
	else if (right) { // && !left
		height = 1 + right->height;
	}
	else { // !left && !right
		height = 1;
	}
}