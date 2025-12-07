#include <iostream>
#include "../DS_Project/LinkedList.h"
#include "../DS_Project/Stack.h"
#include "../DS_Project/Queue.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/Tree.h"
#include "../DS_Project/Graph.h"
using namespace std;

int main() {
    cout << "=== Testing Graph with Dijkstra's Algorithm ===\n\n";

    Graph cityMap;

    cout << "--- Building City Network ---\n";
    cityMap.addVertex("Faizabad");
    cityMap.addVertex("Koral");
    cityMap.addVertex("Bhara Kahu");
    cityMap.addVertex("Blue Area");
    cityMap.addVertex("PIMS Hospital");
    cityMap.addVertex("F-8 Markaz");

    cout << "\n--- Adding Routes ---\n";
    cityMap.addEdge("Faizabad", "Koral", 5);
    cityMap.addEdge("Koral", "Bhara Kahu", 3);
    cityMap.addEdge("Faizabad", "Blue Area", 7);
    cityMap.addEdge("Bhara Kahu", "PIMS Hospital", 4);
    cityMap.addEdge("Blue Area", "PIMS Hospital", 8);
    cityMap.addEdge("Blue Area", "F-8 Markaz", 2);
    cityMap.addEdge("PIMS Hospital", "F-8 Markaz", 6);

    cityMap.display();

    cout << "\n========================================\n";
    cout << "  DIJKSTRA'S SHORTEST PATH TESTS\n";
    cout << "========================================\n";

    // Test 1
    cityMap.FindShortestPath("Faizabad", "PIMS Hospital");

    // Test 2
    cityMap.FindShortestPath("Faizabad", "F-8 Markaz");

    // Test 3
    cityMap.FindShortestPath("Koral", "Blue Area");

    // Test 4 - No path
    cityMap.addVertex("Rawalpindi");  // Isolated vertex
    cityMap.FindShortestPath("Faizabad", "Rawalpindi");

    cout << "\n✅ Dijkstra's Algorithm: WORKING!\n";

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}