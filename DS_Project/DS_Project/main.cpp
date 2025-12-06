#include <iostream>
#include "../DS_Project/LinkedList.h"
#include "../DS_Project/Stack.h"
#include "../DS_Project/Queue.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/Tree.h"
#include "../DS_Project/Graph.h"
using namespace std;

int main() {
    cout << "=== Testing Graph - Part 1 ===\n\n";

    Graph cityMap;

    cout << "--- Adding Bus Stops (Vertices) ---\n";
    cityMap.addVertex("Faizabad");
    cityMap.addVertex("Koral");
    cityMap.addVertex("Bhara Kahu");
    cityMap.addVertex("Blue Area");
    cityMap.addVertex("PIMS Hospital");

    cityMap.addVertex("Rawalpindi");
    cout << "\nPress Enter to continue...";
    cin.get();

    return 0;
}