#pragma once
#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
using namespace std;

class CircularQueue {
private:
	static const int MaxSize = 50;
	string queue[MaxSize];
	int front;
	int rear;
	int size;
	int capacity;

public:
	CircularQueue() :front(0), rear(-1), capacity(MaxSize) {}

	bool isEmpty() {
		return size == 0;
	}

	bool isFull() {
		return size == capacity;
	}

	int getSize() {
		return this->size;
	}

	void enqueue(string passengerName) {
		if (isFull()) {
			cout << "Queue is full\n";
			return;
		}
		rear = (rear + 1) % capacity;
		queue[rear] = passengerName;
		this->size++;
		cout << "Passeneger" << passengerName << "added\n";
	}

	string dequeue() {
		if (isEmpty()) {
			cout << "Queue is empty.\n";
		}

		string passengerName = queue[front];
		front = (front + 1) % capacity;
		size--;
		return passengerName;
	}

	string peek() {
		if (isEmpty()) {
			cout << "Queue is empty\n";
			return "";
		}
		return queue[front];
	}

	void display() {
		if (isEmpty()) {
			cout << "Queue is empty\n";
			return;
		}

		cout << "Queue:\n";
		cout << "Total Passengers: " << size << endl;

		int index = front;
		for (int i = 0; i < size; i++)
		{
			cout << (i + 1) << ". " << queue[index] << "\n";
			index = (index + 1) % capacity;
		}
	}

	void clear() {
		front = 0;
		rear = -1;
		size = 0;
		cout << "Queue is cleared.\n";
	}

};
#endif