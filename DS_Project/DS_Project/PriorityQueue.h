#pragma once
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
using namespace std;

struct HeapNode {
	string Name;
	int priority;

	HeapNode(): Name(""), priority(0){}
	HeapNode(string n, int p):Name(n), priority(p){}
};

class PriorityQueue {
private:
	static const int MaxSize = 100;
	HeapNode heap[MaxSize];
	int size;
	
	int parent(int i) {
		return (i - 1) / 2;
	}
	
	int RightChild(int i) {
		return  (2 * i + 2);
	}

	int LeftChild(int i) {
		return  (2 * i + 1);
	}
	
	void swap(int i, int j) {
		HeapNode TempNode = heap[i];
		heap[i] = heap[j];
		heap[j] = TempNode;
	}

	void HeapifyUp(int index) {
		while (index > 0 && heap[parent(index)].priority < heap[index].priority) {
			swap(index, parent(index));
			index = parent(index);
		}
	}

	void HeapifyDown(int index) {
		int maxIndex = index;
		int left = LeftChild(index);
		int right = RightChild(index);

		if (left < size && heap[left].priority > heap[maxIndex].priority) {
			maxIndex = left;
		}
		
		if (right < size && heap[right].priority > heap[maxIndex].priority) {
			maxIndex = right;
		}

		if (index != maxIndex) {
			swap(index, maxIndex);
			HeapifyDown(maxIndex);
		}
	}
public:
    PriorityQueue() : size(0) {}



    void insert(string name, int priority) {
        if (size >= MaxSize) {
            cout << "Priority Queue is full!\n";
            return;
        }



        heap[size] = HeapNode(name, priority);



        HeapifyUp(size);

        size++;

        cout << "Inserted: " << name << " (Priority: " << priority << " beds)\n";
    }



    HeapNode peek() {
        if (isEmpty()) {
            cout << "Priority Queue is empty!\n";
            return HeapNode();
        }
        return heap[0];
    }

    HeapNode extractMax() {
        if (isEmpty()) {
            cout << "Priority Queue is empty!\n";
            return HeapNode();
        }

        HeapNode maxNode = heap[0];



        heap[0] = heap[size - 1];
        size--;


        if (size > 0) {
            HeapifyDown(0);
        }

        return maxNode;
    }
    bool isEmpty() {
        return size == 0;
    }


    int getSize() {
        return size;
    }
    void display() {
        if (isEmpty()) {
            cout << "Priority Queue is empty\n";
            return;
        }

        cout << "\n=== Priority Queue (Max-Heap) ===\n";
        cout << "Hospital Name          | Available Beds\n";
        cout << "---------------------------------------\n";

        for (int i = 0; i < size; i++) {
            cout << heap[i].Name;


            for (int j = heap[i].Name.length(); j < 23; j++) {
                cout << " ";
            }

            cout << "| " << heap[i].priority << " beds\n";
        }

        cout << "\nTop Priority: " << heap[0].Name << " (" << heap[0].priority << " beds)\n";
    }

    void displayTree() {
        if (isEmpty()) {
            cout << "Priority Queue is empty\n";
            return;
        }

        cout << "\n=== Heap Tree Structure ===\n";
        displayTreeHelper(0, 0);
    }

private:
    void displayTreeHelper(int index, int level) {
        if (index >= size)
        {
            return;
        }


        displayTreeHelper(RightChild(index), level + 1);

        for (int i = 0; i < level; i++) {
            cout << "    ";
        }
        cout << "[" << heap[index].Name << ":" << heap[index].priority << "]\n";


        displayTreeHelper(LeftChild(index), level + 1);
    }
};

#endif // !PRIORITYQUEUE_H
