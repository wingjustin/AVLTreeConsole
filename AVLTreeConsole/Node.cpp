#include "BinarySearchTree.h"

using namespace BinarySearchTree;

Node::Node() {
	parent = NULL;
	left = NULL;
	right = NULL;
	// data
	Node::key = INT32_MIN;
	Node::value = "";
}

Node::Node(int key){
	//initialize node status
	parent = NULL;
	left = NULL;
	right = NULL;
	// data
	Node::key = key;
	Node::value = "";
}

Node::Node(int key, string value){
	//initialize node status
	parent = NULL;
	left = NULL;
	right = NULL;
	// data
	Node::key = key;
	Node::value = value;
}

Node::~Node(){
	delete left;
	delete right;

	parent = NULL;
	left = NULL;
	right = NULL;
}

//data
int Node::GetKey(){
	return key;
}

string Node::GetValue(){
	return value;
}

void Node::SetValue(string value){
	Node::value = value;
}
