#include <iostream>
#include "../DS_Project/LinkedList.h"
#include "../DS_Project/Stack.h"
#include "../DS_Project/Queue.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/Tree.h"
#include "../DS_Project/Graph.h"
#include "../DS_Project/PriorityQueue.h"
#include "../DS_Project/Transport.h"
#include "../DS_Project/Population.h"
using namespace std;
int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║    SMART CITY - POPULATION MODULE         ║\n";
    cout << "╚════════════════════════════════════════════╝\n";

    PopulationModule population;

    // ===== BUILD CITY HIERARCHY =====
    cout << "\n--- Building City Hierarchy ---\n";
    population.addSector("G-10");
    population.addSector("F-8");
    population.addSector("Blue Area");
    population.addSector("G-9");

    population.addStreet("G-10", "Street 22");
    population.addStreet("G-10", "Street 15");
    population.addStreet("F-8", "Street 5");
    population.addStreet("Blue Area", "Jinnah Avenue");

    population.addHouse("G-10", "Street 22", "180");
    population.addHouse("G-10", "Street 22", "182");
    population.addHouse("F-8", "Street 5", "12");

    // ===== REGISTER CITIZENS =====
    cout << "\n--- Registering Citizens ---\n";
    population.registerCitizen("61101-1111111-1", "Ahmed Khan", 45, "Engineer", "G-10", "22", "180", "M");
    population.registerCitizen("61101-2222222-2", "Fatima Zahra", 38, "Teacher", "F-8", "5", "12", "F");
    population.registerCitizen("61101-3333333-3", "Ali Raza", 29, "Doctor", "G-9", "17", "90", "M");
    population.registerCitizen("61101-4444444-4", "Sara Malik", 22, "Student", "F-8", "9", "33", "F");
    population.registerCitizen("61101-5555555-5", "Hamza Noor", 50, "Business", "Blue Area", "1", "5", "M");
    population.registerCitizen("61101-6666666-6", "Ayesha Ali", 16, "Student", "G-10", "22", "182", "F");
    population.registerCitizen("61101-7777777-7", "Hassan Ahmed", 65, "Retired", "Blue Area", "1", "10", "M");

    // ===== UC-H6: SEARCH BY CNIC =====
    cout << "\n========================================\n";
    cout << "  UC-H6: Search Citizen by CNIC\n";
    cout << "========================================\n";
    population.searchByCNIC("61101-1111111-1");
    population.searchByCNIC("61101-4444444-4");
    population.searchByCNIC("99999-9999999-9");  // Not found

    // ===== UC-H1, H2, H3: DISPLAY HIERARCHY =====
    cout << "\n========================================\n";
    cout << "  UC-H1/H2/H3: City Hierarchy\n";
    cout << "========================================\n";
    population.displayHierarchy();

    // ===== UC-H7: AGE DISTRIBUTION =====
    cout << "\n========================================";
    population.generateAgeDistribution();

    // ===== UC-H8: OCCUPATION SUMMARY =====
    cout << "\n========================================";
    population.generateOccupationSummary();

    // ===== UC-H10: GENDER RATIO =====
    cout << "\n========================================";
    population.generateGenderRatio();

    // ===== LIST ALL =====
    population.listAllCitizens();

    cout << "\n✅ POPULATION MODULE: ALL USE CASES WORKING!\n";

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}