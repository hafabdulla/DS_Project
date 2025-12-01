/*****************************************************************//**
 * @file   main.cpp
 * @brief  Application Entry Point (Presentation Layer).
 *
 * @author Fahad Hassan
 * @date   1 11 2025
 *********************************************************************/

#include <iostream>
#include <string>
#include <Domain/Transport/TransportService.h>
#include <Domain/Transport/IBusRepository.h>
#include <Infrastructure/CCsvBusRepository.h>

using namespace std;

void RunTransportModule(TransportService& service)
{
    cout << "\n==========================================" << endl;
    cout << "  TRANSPORT MODULE: UC-T9 Display Route" << endl;
    cout << "==========================================" << endl;

    // List available bus IDs for testing reference based on buses.csv
    cout << "Available Buses: B101, B102, B201, B305, B402" << endl;

    string inputID;
    cout << "Enter Bus ID (e.g., B101): ";
    cin >> inputID;

    // Call Service Layer (The Domain Logic)
    const LinkedList<std::string>* route = service.GetBusRoute(inputID);

    // Presentation Layer handles the output based on the returned data
    cout << "\n------------------------------------------" << endl;

    if (route != nullptr)
    {
        cout << "Route for " << inputID << ":\n";

        // Use the STL-style iterator provided by SLList.h
        bool first = true;
        for (const auto& stopName : *route)
        {
            if (!first)
            {
                cout << " -> ";
            }
            cout << "[" << stopName << "]";
            first = false;
        }
        cout << "\n------------------------------------------" << endl;
    }
    else
    {
        cout << "Error: Bus ID '" << inputID << "' not found in the system." << endl;
        cout << "------------------------------------------" << endl;
    }
}


int main()
{
    // --- 1. INFRASTRUCTURE & DEPENDENCY INJECTION ---

    // We create the concrete repository (Infrastructure)
    // The path assumes the executable is run from the project root or the CSV is copied there.
    IBusRepository* busRepo = new CsvBusRepository("data/buses.csv");

    // We inject the repository into the Service (Domain)
    TransportService transportService(busRepo);

    // --- 2. INITIALIZATION (Load Data) ---

    // Tell the service to load data from the repo into its internal cache (m_Buses)
    cout << "System Initialization: Loading data..." << endl;
    transportService.Initialize();
    cout << "Initialization complete." << endl;

    // --- 3. PRESENTATION ---

    RunTransportModule(transportService);

    // --- 4. CLEANUP ---

    delete busRepo;
    return 0;
}