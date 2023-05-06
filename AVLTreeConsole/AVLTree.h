#pragma once

#include <string>

using namespace std;

namespace BinarySearchTree {
	class AVLTree : public Tree{
	private:
		bool HealthCheck(AVLNode* current, int& currentHeight); // for debug
	protected:
		AVLNode* root;

		void clockwiseRotation(AVLNode* target);
		void counter_clockwiseRotation(AVLNode* target);

		void Rebalance(AVLNode* target);
	public:
		AVLTree();
		~AVLTree();

		void Clear();

		AVLNode* SearchNode(int key);
		void Insert(int key, string value);
		bool Remove(int key); //return success

		bool HealthCheck(); // for debug
	};
}
