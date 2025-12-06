#pragma once
#ifndef Queue_H
#define Queue_H
#include <iostream>
using namespace std;

struct QueueNode {
	string Data;
	QueueNode* Next;

	QueueNode(string D):Data(D), Next(NULL){}
};
class MyQueue {
private:
	QueueNode* Front;
	QueueNode* Rear;
	int Size;
public:
	MyQueue() : Front(nullptr), Rear(nullptr), Size(0){}
	~MyQueue() {
		while (!isEmpty()) {
			dequeue();
		}
	}

	void enqueue(string InputValue) {
		QueueNode* NewNode = new QueueNode(InputValue);
		if (isEmpty()) {
			Front = Rear = NewNode;
		}
		else {
			Rear->Next = NewNode;
			Rear = NewNode;
		}
			Size++;
	}
	string dequeue() {
		if (isEmpty()) {
			cout << "Empty Queue\n";
			return "";
		}
		QueueNode* TempNode = Front;
		string TempVal = Front->Data;
		Front = Front->Next;

		if (Front == NULL) {
			Rear = NULL;
		}
		delete TempNode;
		Size--;
		return TempVal;
	}
	string peek() {
		if (isEmpty()) {
			cout << "Empty Queue\n";
			return "";
		}
		return Front->Data;
	}

	bool isEmpty() {
		return Front == NULL;
	}

	int getSize() {
		return Size;
	}

	void display() {
		if (isEmpty()) {
			cout << "Empty Queue\n";
			return;
		}

		cout << "Queue (front to rear): ";
		QueueNode* TempNode = Front;
		while (TempNode != nullptr) {
			cout << TempNode->Data;
			if (TempNode->Next != nullptr) {
				cout << " -> ";
			}
			TempNode = TempNode->Next;
		}
		cout << endl;
	}
};
#endif // !Queue
