#pragma once
#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

class StackNode {
public:
	string Data;
	StackNode* Next;
	StackNode(string D):Data(D), Next (nullptr){}
};

class Stack {
private:
	StackNode* Top;
	int size;

public:
	Stack():Top(nullptr), size(0){}
	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}

	void push(string InputValue) {
		StackNode* NewNode = new StackNode(InputValue);
		NewNode->Next = Top;
		Top = NewNode;
		this->size++;
	}

	string pop() {
		if (isEmpty()) {
			cout << "Empty Stack\n";
		}
		StackNode* TempNode = Top;
		string TempVal = Top->Data;
		Top = Top->Next;
		delete TempNode;
		size--;
		return TempVal;
	}
	string peek() {
		if (isEmpty()) {
			cout << "Empty Stack\n";
		}
		return Top->Data;
	}

	bool isEmpty() {
		return Top == NULL;
	}

	int getSize() {
		return this->size;
	}

	void display() {
		if (isEmpty()) {
			cout << "Empty Stack";
			return;
		}
		cout << "Stack (Top -> Bottom):";
		StackNode* TempNode = Top;
		while (TempNode != nullptr) {
			cout << TempNode->Data;
			if (TempNode->Next != NULL) {
				cout << " -> ";
			}
			TempNode = TempNode->Next;
		}
		cout << "\n";
	}
};
#endif // !1
