/*****************************************************************//**
 * @file   main.cpp
 * @brief  Application Entry Point (Presentation Layer).
 *
 * @details Initializes the Population module and runs UC-H6 (Search Citizen by CNIC).
 *
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#include <iostream>
#include <string>

 // Domain Headers
#include <Domain/PopulationService.h>
#include <Domain/IPersonRepository.h>

// Infrastructure Header
#include <Infrastructure/CCsvPersonRepository.h>

using namespace std;

// Forward declaration for the menu function
void RunPopulationModule(PopulationService& service);

int main()
{
    // --- 1. INFRASTRUCTURE & DEPENDENCY INJECTION ---

    // We dynamically allocate the concrete repository (Infrastructure).
    // The path is set to the correct population data file.
    IPersonRepository* populationRepo = new CCsvPersonRepository("data/population.csv");

    // We inject the repository into the Service (Domain)
    PopulationService populationService(populationRepo);

    // --- 2. INITIALIZATION (Load Data) ---

    // Tell the service to load data from the repo into its internal cache (HashTable)
    cout << "System Initialization: Loading data..." << endl;
    populationService.Initialize();
    cout << "Initialization complete. Hash Table ready." << endl;

    // --- 3. PRESENTATION ---

    RunPopulationModule(populationService);

    // --- 4. CLEANUP ---

    delete populationRepo;
    return 0;
}

void RunPopulationModule(PopulationService& service)
{
    cout << "\n==========================================" << endl;
    cout << "  POPULATION MODULE: UC-H6 Search Citizen" << endl;
    cout << "==========================================" << endl;

    // List sample CNICs for testing based on population.csv
    cout << "Sample CNICs for testing:" << endl;
    cout << "  - 61101-1111111-1 (Engineer)" << endl;
    cout << "  - 61101-4444444-4 (Student)" << endl;

    string inputCNIC;
    cout << "\nEnter Citizen CNIC: ";
    cin >> inputCNIC;

    // Call Service Layer (The Domain Logic) - O(1) Average Lookup
    const Person* citizen = service.GetCitizen(inputCNIC);

    // Presentation Layer handles the output
    cout << "\n------------------------------------------" << endl;

    if (citizen != nullptr)
    {
        cout << "Citizen Found:" << endl;
        cout << "  Name:       " << citizen->GetName() << endl;
        cout << "  CNIC:       " << citizen->GetCNIC() << endl;
        cout << "  Age:        " << citizen->GetAge() << endl;
        cout << "  Occupation: " << citizen->GetOccupation() << endl;
        cout << "  Address:    " << citizen->GetAddress() << endl;
    }
    else
    {
        cout << "Error: Citizen with CNIC '" << inputCNIC << "' not found." << endl;
    }
    cout << "------------------------------------------" << endl;
}