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

	void addEdge(string Source, string Destination, int weight) {
		int SourceIndex = findVertexIndex(Source);
		int DestinationIndex = findVertexIndex(Destination);

		if (SourceIndex == -1) {
			cout << "Error: Vertex '" << Source << "' not found!\n";
			return;
		}
		if (DestinationIndex == -1) {
			cout << "Error: Vertex '" << Destination << "' not found!\n";
			return;
		}

		vertices[SourceIndex]->addEdge(Destination, weight);
		vertices[DestinationIndex]->addEdge(Source, weight);

		cout << "Added edge from " << Source << " to " << Destination << " with weight : " << weight << endl;
	}

	void display() {
		cout << " Graph Structure \n";
		for (int i = 0; i < VertexCount; i++)
		{
			cout << vertices[i]->name << "->";
			Edge* edge = vertices[i]->adjacencyList;
			if (edge == nullptr) {
				cout << "Not Connected\n";
			}
			else {
				while (edge != nullptr) {
					cout << "[" << edge->destination << ", " << edge->weight << "km]";
					if (edge->next != nullptr) {
						cout << "->";
					}
					edge = edge->next;
				}
			}
			cout << "\n";
		}
		cout << "Total Vertices: " << VertexCount << endl;
	}

	void FindShortestPath(string start, string end) {
		int startIndex = findVertexIndex(start);
		int endIndex = findVertexIndex(end);

		if (startIndex == -1 || endIndex == -1) {
			cout << "Start or ending not found\n";
			return;
		}
		int distances[MaxVertices];
		bool visited[MaxVertices];
		int previous[MaxVertices];


		for (int i = 0; i < VertexCount; i++)
		{
			distances[i] = 999999; //infinity
			visited[i] = false;
			previous[i] = -1;
		}

		distances[startIndex] = 0;
		for (int count = 0; count < VertexCount; count++)
		{
			int minDistance = 999999;
			int minIndex = -1;
			for (int i = 0; i < VertexCount; i++)
			{
				if (!visited[i] && distances[i] < minDistance) {
					minDistance = distances[i];
					minIndex = i;
				}
			}

			if (minIndex == -1) {
				break;
			}

			visited[minIndex] = true;

			Edge* edge = vertices[minIndex]->adjacencyList;
			while (edge != nullptr) {
				int neighborIndex = findVertexIndex(edge->destination);

				if (!visited[neighborIndex]) {
					int newDistance = distances[minIndex] + edge->weight;

					if (newDistance < distances[neighborIndex]) {
						distances[neighborIndex] = newDistance;
						previous[neighborIndex] = minIndex;
					}
				}

				edge = edge->next;
			}
		}
		cout << "\n=== Shortest Path: " << start << " to " << end << " ===\n";

		if (distances[endIndex] == 999999) {
			cout << "No path exists!\n";
			return;
		}

		cout << "Total Distance: " << distances[endIndex] << " km\n";
		cout << "Path: ";

		int path[MaxVertices];
		int pathLength = 0;
		int current = endIndex;

		while (current != -1) {
			path[pathLength++] = current;
			current = previous[current];
		}

		for (int i = pathLength - 1; i >= 0; i--) {
			cout << vertices[path[i]]->name;
			if (i > 0) cout << " -> ";
		}
		cout << "\n";
	}
};

#endif // !
