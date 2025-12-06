#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	string data;
	Node* next;

	Node(string val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
	Node* head;
	int size;
public:
	LinkedList() : head(nullptr), size(0) {}

	~LinkedList() {
		Node* current = head;
		while (current != NULL) {
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}

	void insert(string InputValue) {
		Node* NewNode = new Node(InputValue);
		if (head == nullptr) {
			head = NewNode;
		}
		else {
			Node* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = NewNode;
		}
		size++;
	}

	void display() {
		if (head == nullptr) {
			cout << "Empty List" << endl;
			return;
		}
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data;
			if (temp->next != nullptr) {
				cout << " -> ";
			}
			temp = temp->next;
		}
		cout << endl;
	}

	bool search(string InputValue) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->data == InputValue) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return head == nullptr;
	}
};
#endif