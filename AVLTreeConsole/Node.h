#pragma once

#include <string>

using namespace std;

namespace BinarySearchTree{
	class Node{
	protected:
		// node status
		Node* parent;
		Node* left;
		Node* right;
		// data
		int key;
		string value;

		friend class Tree;
	public:
		Node();
		Node(int key);
		Node(int key, string value);
		~Node();

		// data
		//**key
		int GetKey();
		//**value
		string GetValue();
		void SetValue(string value);
	};
}
