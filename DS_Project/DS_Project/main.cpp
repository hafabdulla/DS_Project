#include <iostream>
#include "../DS_Project/LinkedList.h"
#include "../DS_Project/Stack.h"
#include "../DS_Project/Queue.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/Tree.h"
#include "../DS_Project/Graph.h"
#include "../DS_Project/PriorityQueue.h"
using namespace std;

int main() {
    cout << "=== Testing Priority Queue (Emergency Beds) ===\n\n";

    PriorityQueue emergencyQueue;

    cout << "--- Registering Hospitals with Bed Availability ---\n";
    emergencyQueue.insert("PIMS Hospital", 12);
    emergencyQueue.insert("Shifa International", 20);
    emergencyQueue.insert("Maroof Hospital", 8);
    emergencyQueue.insert("Poly Clinic", 14);
    emergencyQueue.insert("Islamabad Medical", 10);

    emergencyQueue.display();

    cout << "\n========================================\n";
    cout << "  EMERGENCY SITUATION!\n";
    cout << "========================================\n";

    // Ambulance needs hospital with most beds
    cout << "\nAmbulance 1 needs emergency bed...\n";
    HeapNode best = emergencyQueue.peek();
    cout << "Best option: " << best.Name << " (" << best.priority << " beds available)\n";

    cout << "\n--- Sending patient to " << best.Name << " ---\n";
    HeapNode selected = emergencyQueue.extractMax();
    cout << "Patient admitted to: " << selected.Name << "\n";
    cout << "Beds used: 1\n";

    // Update bed count (one bed used)
    emergencyQueue.insert(selected.Name, selected.priority - 1);

    cout << "\n--- Updated Hospital Status ---\n";
    emergencyQueue.display();

    cout << "\n--- Another Emergency! ---\n";
    HeapNode next = emergencyQueue.extractMax();
    cout << "Next patient sent to: " << next.Name << " (" << next.priority << " beds)\n";

    emergencyQueue.display();

    cout << "\n--- Visualizing Heap Structure ---\n";
    emergencyQueue.displayTree();

    cout << "\n✅ Priority Queue: MAX-HEAP WORKING!\n";

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}