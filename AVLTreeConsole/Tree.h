#pragma once

#include <string>

using namespace std;

namespace BinarySearchTree{
	class Tree{
	protected:
		Node* root;
	public:
		Tree();
		~Tree();

		Node* SearchNode(int key);
		void Insert(int key, string value);
		bool Remove(int key); //return success
	};
}
