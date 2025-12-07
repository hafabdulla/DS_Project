/*****************************************************************//**
 * @file   main.cpp
 * @brief  Application Entry Point (Presentation Layer).
 * Provides a console-based UI for Smart City Management.
 *
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#include <string>
#include <iostream>
#include "TransportMenu.h"
#include "HousingMenu.h"

using namespace std;

void clearInputBuffer()
{
    cin.ignore(1000000, '\n');
}

int main()
{
    // 1. Initialize Domain Services
    TransportService transportService;
    HousingService housingService;

    // 2. Main Application Loop
    cout << "========================================\n";
    cout << "   SMART CITY MANAGEMENT SYSTEM v1.0    \n";
    cout << "========================================\n";

    int choice = -1;
    while (choice != 0) {
        cout << "\n--- Main Dashboard ---\n";
        cout << "1. Transport Department\n";
        cout << "2. Population Department\n";
        cout << "0. Exit Application\n";
        cout << "Select an option: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            manageTransport(transportService);
            break;
        case 2:
            managePopulation(housingService);
            break;
        case 0:
            cout << "Shutting down system. Goodbye!\n";
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            break;
        }
    }

    return 0;
}