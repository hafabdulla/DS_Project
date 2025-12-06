#pragma once
#ifndef TREE_H
#define TREE_H
#include <iostream>
using namespace std;
struct TreeNode {
	string data;
	TreeNode* children[50];
	int childCount;

	TreeNode(string value) :data(value), childCount(0) {
		for (int  i = 0; i < 50; i++)
		{
			children[i] = nullptr;
		}
	}

	void addChild(TreeNode* child) {
		if (childCount < 50) {
			children[childCount] = child;
			childCount++;
		}
		else {
			cout << "Children Limit Reached\n";
		}
	}
};

class Tree {
private:
	TreeNode* root;
public:
	Tree(string rootData) {
		root = new TreeNode(rootData);
	}

	TreeNode* getRoot() {
		return root;
	}
};
#endif // !TREE_H
