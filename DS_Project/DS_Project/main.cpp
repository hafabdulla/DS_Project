#include <iostream>
#include "../DS_Project/LinkedList.h"
#include "../DS_Project/Stack.h"
#include "../DS_Project/Queue.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/Tree.h"
#include "../DS_Project/Graph.h"
#include "../DS_Project/PriorityQueue.h"
#include "../DS_Project/Transport.h"
using namespace std;

int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║     SMART CITY - TRANSPORT MODULE         ║\n";
    cout << "╚════════════════════════════════════════════╝\n";

    TransportModule transport;

    // ===== SETUP CITY NETWORK =====
    cout << "\n--- Building City Network ---\n";
    transport.addBusStop("Faizabad");
    transport.addBusStop("Koral");
    transport.addBusStop("Bhara Kahu");
    transport.addBusStop("Blue Area");
    transport.addBusStop("PIMS Hospital");
    transport.addBusStop("F-8 Markaz");

    cout << "\n--- Connecting Stops ---\n";
    transport.connectStops("Faizabad", "Koral", 5);
    transport.connectStops("Koral", "Bhara Kahu", 3);
    transport.connectStops("Faizabad", "Blue Area", 7);
    transport.connectStops("Bhara Kahu", "PIMS Hospital", 4);
    transport.connectStops("Blue Area", "PIMS Hospital", 8);
    transport.connectStops("Blue Area", "F-8 Markaz", 2);

    // ===== REGISTER BUSES =====
    cout << "\n--- Registering Buses ---\n";
    transport.registerBus("B101", "Metro Bus");
    transport.registerBus("B102", "Capital Transport");
    transport.registerBus("B201", "Green Wheels");

    // ===== ADD ROUTES TO BUSES =====
    cout << "\n--- Setting Up Bus Routes ---\n";
    transport.addStopToBus("B101", "Faizabad");
    transport.addStopToBus("B101", "Koral");
    transport.addStopToBus("B101", "Bhara Kahu");
    transport.addStopToBus("B101", "PIMS Hospital");

    transport.addStopToBus("B102", "Blue Area");
    transport.addStopToBus("B102", "F-8 Markaz");

    // ===== UC-T9: DISPLAY BUS ROUTE =====
    cout << "\n========================================\n";
    cout << "  UC-T9: Display Complete Bus Route\n";
    cout << "========================================\n";
    transport.displayBusRoute("B101");
    transport.displayBusRoute("B102");

    // ===== UC-T10: ROUTE HISTORY =====
    cout << "\n========================================\n";
    cout << "  UC-T10: Track Bus Movement\n";
    cout << "========================================\n";
    transport.moveBus("B101", "Faizabad");
    transport.moveBus("B101", "Koral");
    transport.moveBus("B101", "Bhara Kahu");

    transport.showBusHistory("B101");

    // ===== UC-T7: SEARCH BUS =====
    cout << "\n========================================\n";
    cout << "  UC-T7: Search Bus by Number\n";
    cout << "========================================\n";
    transport.searchBus("B101");
    transport.searchBus("B999");

    // ===== UC-T6: SHORTEST PATH =====
    cout << "\n========================================\n";
    cout << "  UC-T6: Find Shortest Path\n";
    cout << "========================================\n";
    transport.findShortestPath("Faizabad", "PIMS Hospital");
    transport.findShortestPath("Blue Area", "Bhara Kahu");

    // ===== LIST ALL BUSES =====
    cout << "\n========================================\n";
    cout << "  All Registered Buses\n";
    cout << "========================================\n";
    transport.listAllBuses();

    // ===== DISPLAY NETWORK =====
    cout << "\n========================================\n";
    cout << "  Complete City Network\n";
    cout << "========================================\n";
    transport.displayNetwork();

    cout << "\n✅ TRANSPORT MODULE: ALL USE CASES WORKING!\n";

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}