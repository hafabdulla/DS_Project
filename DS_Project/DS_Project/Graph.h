#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

struct Edge {
public:
	string destination;
	int weight;
	Edge* next;
	Edge(string dest, int w):destination(dest), weight(w), next (nullptr){}
};

struct Vertex {
	string name;
	Edge* adjacencyList;

	Vertex(string n): name(n), adjacencyList(nullptr){}

	void addEdge(string destination, int weight) {
		Edge* newEdge = new Edge(destination, weight);

		newEdge->next = adjacencyList;
		adjacencyList = newEdge;
	}
};

class Graph {
private:
	static const int MaxVertices = 100;
	Vertex* vertices[MaxVertices];
	int VertexCount;

private:
	int findVertexIndex(string name) {
		for (int i = 0; i < VertexCount; i++) {
			if (vertices[i]->name == name) {
				return i;
			}
		}
		return -1;
	}
public:
	Graph() :VertexCount(0) {
		for (int i = 0; i < MaxVertices; i++) {
			vertices[i] = nullptr;
		}
	}

	void addVertex(string name) {
		if (findVertexIndex(name) != -1) {
			cout << "Vertex '" << name << "' already exists\n";
			return;
		}
		if (VertexCount >= MaxVertices)
		{
			cout << "Full Graph\n";
			return;
		}

		vertices[VertexCount] = new Vertex(name);
		VertexCount++;
		cout << "Added " << name << " Stop (Vertex).\n";
	}
};

#endif // !
