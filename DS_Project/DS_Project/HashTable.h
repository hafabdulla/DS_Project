#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

using namespace std;

struct HashNode {
	string key;
	string value;
	HashNode* next;

	HashNode(string k, string v):key(k), value(v), next(nullptr){}
};

class HashTable {
private:
	static const int TableSize = 100;
	HashNode* table[TableSize];

	int hashFunction(string key) {
		int hash = 0;
		int prime = 3;

		for (int i = 0; i < key.length(); i++)
		{
			hash = (hash * prime + key[i]) % this->TableSize;
		}
		return hash;
	}
public:
	HashTable() {
		for (int i = 0; i < TableSize; i++)
		{
			table[i] = nullptr;
		}
	}

	void insert(string key, string value) {
		int index = hashFunction(key);

		HashNode* newNode = new HashNode(key, value);
		newNode->next = table[index];
		table[index] = newNode;

		cout << key << " -> " << value << "Inserted at index: " << index << endl;
	}

	string search(string key) {
		int index = hashFunction(key);

		HashNode* current = table[index];

		while (current != nullptr) {
			if (current->key == key) {
				return current->value;
			}
			current = current->next;
		}
		return "";
	}

	void display() {
		cout << "Hash Table Contents:\n";

		int totalEntries = 0;
		for (int i = 0; i < this->TableSize; i++)
		{
			if(table[i] != nullptr){
				cout << "Index: " << i << ": ";
				HashNode* current = table[i];
				while (current != nullptr) {
					cout << "[" << current->key << ": " << current->value << "]";
					if (current->next != nullptr) {
						cout << "->";
					}
					current = current->next;
					totalEntries++;
				}
				cout << endl;
			}
		}
		cout << "Total Entries: " << totalEntries << endl;
	}
};
#endif // !HASHTABLE_H
