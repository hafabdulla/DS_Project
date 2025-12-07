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
	TreeNode* searchHelper(TreeNode* node, string value) {
		if (node == nullptr) {
			return nullptr;
		}

		if (node->data == value) {
			return node;
		}
		for (int i = 0; i < node->childCount; i++)
		{
			TreeNode* result = searchHelper(node->children[i], value);
			if (result != nullptr) {
				return result;
			}
		}
		return nullptr;
	}

	void displayHelper(TreeNode* node, int level) {
		if (node == nullptr) {
			return;
		}
		for (int  i = 0; i < level; i++)
		{
			cout << " "; //indentation
		}
		if (level == 0) {
			cout << node->data << "(Root)\n";
		}
		else {
			cout << "|___ " << node->data << "\n";
		}

		for (int i = 0; i < node->childCount; i++)
		{
			displayHelper(node->children[i], level + 1);
		}
	}
public:
	Tree(string rootData) {
		root = new TreeNode(rootData);
	}

	TreeNode* getRoot() {
		return root;
	}

	TreeNode* search(TreeNode* startNode, string value) {
		return searchHelper(startNode, value);
	}

	void display() {
		displayHelper(root, 0);
	}
};
#endif // !TREE_H
