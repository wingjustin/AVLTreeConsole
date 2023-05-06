#include "BinarySearchTree.h"

using namespace BinarySearchTree;

AVLTree::AVLTree(){
	root = NULL;
}

AVLTree::~AVLTree(){
	delete root;
	root = NULL;
}

void AVLTree::Clear() {
	delete root;
	root = NULL;
}

void AVLTree::clockwiseRotation(AVLNode* const target){
	if (!target || !target->left)
		return;
	//move left child to parent
	AVLNode* temp = target->parent;
	if (temp){
		if (temp->left == target)
			temp->left = target->left;
		else // if (target->parent->right == target)
			temp->right = target->left;
		target->left->parent = temp;
	}
	else {
		target->left->parent = NULL;
		if (target == root)
			root = target->left;
	}
	//move old parent to right child of new parent
	temp = target->left;
	target->parent = temp;
	if (temp->right){
		//move new parent's right child to old parent's left
		temp->right->parent = target;
		target->left = temp->right;
		temp->right = target;
	}
	else{
		target->left = NULL;
		temp->right = target;
	}
	temp = NULL;
	//update height
	target->UpdateHeight();
	target->parent->UpdateHeight();
}

void AVLTree::counter_clockwiseRotation(AVLNode* const target){
	if (!target || !target->right)
		return;
	//move right child to parent
	AVLNode* temp = target->parent;
	if (temp){
		if (temp->left == target)
			temp->left = target->right;
		else // if (temp->right == target)
			temp->right = target->right;
		target->right->parent = temp;
	}
	else {
		target->right->parent = NULL;
		if (target == root)
			root = target->right;
	}
	//move old parent to left child of new parent
	temp = target->right;
	target->parent = temp;
	if (temp->left){
		//move new parent's left child to old parent's right
		temp->left->parent = target;
		target->right = temp->left;
		temp->left = target;
	}
	else{
		target->right = NULL;
		temp->left = target;
	}
	temp = NULL;
	//update height
	target->UpdateHeight();
	target->parent->UpdateHeight();
}

void AVLTree::Rebalance(AVLNode* target) { // Check balance of current -> child -> grandchild
	int diff = 0;
	while (target) {
		diff = target->LeftCompareRight();
		if (diff > 1) { // L>R =L
			diff = target->left->LeftCompareRight();
			if (diff < 0) { // L<R =LR
				counter_clockwiseRotation(target->left);
				clockwiseRotation(target);
				target = target->parent;
			}
			else { // if (diff >= 0){ // L>R =LL
				clockwiseRotation(target);
				target = target->parent;
			}
		}
		else if (diff < -1) { // L<R =R
			diff = target->right->LeftCompareRight();
			if (diff > 0) { // L>R =RL
				clockwiseRotation(target->right);
				counter_clockwiseRotation(target);
				target = target->parent;
			}
			else {// if (diff <= 0){ // L<R =RR
				counter_clockwiseRotation(target);
				target = target->parent;
			}
		}
		target = target->parent;
		if (target)
			target->UpdateHeight();
	}
}

AVLNode* AVLTree::SearchNode(const int key){
	// return NULL if empty
	if (!root)
		return NULL;
	// search from root
	if (key == root->key)
		return root;
	AVLNode* cNode = root; // current node
	do {
		cNode = key < cNode->key
			? cNode->left    // go left if less than current node
			: cNode->right;  // go right if greater than current node
	} while (cNode && key != cNode->key);// continue if child is not NULL and not match.
	return cNode;
}

void AVLTree::Insert(const int key, const string value){
	if (!root){
		root = new AVLNode(key, value);
		return;
	}
	//search insert entry
	AVLNode* entry = root;
	AVLNode* next = NULL;
	bool isLeft = 0; // 0 = right, 1 = left
	do {
		if (key == entry->key) { // if the key is equal, replace value and return it.
			entry->value = value;
			return;
		}
		next = (isLeft = key < entry->key)
			? entry->left    // go left if less than current node
			: entry->right;  // go right if greater than current node
	} while (next && (entry = next));
	//start to insert new node
	AVLNode* nNode = new AVLNode(key, value);
	nNode->parent = entry;
	if (isLeft)
		entry->left = nNode;
	else
		entry->right = nNode;
	entry->UpdateHeight();
	Rebalance(entry);

	while (root->parent)
		root = root->parent;

	entry = NULL;
	next = NULL;
}

bool AVLTree::Remove(const int key) {//return success
	if (!root)
		return false;
	// search from root
	AVLNode* cNode = root; // current node
	if (key != cNode->key) {
		do {
			cNode = key < cNode->key
				? cNode->left    // go left if less than current node
				: cNode->right;  // go right if greater than current node
		} while (cNode && key != cNode->key);// continue if child is not NULL and not match.
	}
	if (cNode) {
		//find out the Node of near key
		AVLNode* temp = cNode;
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
			AVLNode* rebalanceTarget = temp->parent;
			//delete Node
			temp->left = NULL;
			temp->right = NULL;
			temp->parent = NULL;
			delete temp;
			temp = NULL;
			//rebalance
			rebalanceTarget->UpdateHeight();
			Rebalance(rebalanceTarget);
			rebalanceTarget = NULL;
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

// for debug
bool AVLTree::HealthCheck(AVLNode* current, int& currentHeight) {
	int leftHeight = 0;
	int rightHeight = 0;
	if (current->left && (current->left->key <= current->key) && !HealthCheck(current->left, leftHeight)) // check left child and return its height
		return false;
	else if (current->right && (current->right->key >= current->key) && !HealthCheck(current->right, rightHeight)) // check right child and return its height
		return false;
	currentHeight = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // check current height if it is correct
	int diff = leftHeight - rightHeight; // check height difference between left and right is not more than 1;
	return currentHeight == current->height && (diff > -2 && diff < 2);
}

bool AVLTree::HealthCheck() {
	int treeHeight = 0;
	return !root
		|| (!root->parent
			&& (HealthCheck(root, treeHeight) && treeHeight == root->height)
			);
}