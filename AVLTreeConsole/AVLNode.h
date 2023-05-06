#pragma once

#include <string>

using namespace std;

namespace BinarySearchTree{
	class AVLNode : public Node {
	protected:
		// node status
		unsigned long height;
		AVLNode* parent;
		AVLNode* left;
		AVLNode* right;

		int LeftCompareRight();
		void UpdateHeight();

		friend class AVLTree;
	public:
		AVLNode(int key);
		AVLNode(int key, string value);
		~AVLNode();
	};
}
