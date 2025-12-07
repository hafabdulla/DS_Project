/*****************************************************************//**
 * @file   main.cpp
 * @brief  Application Entry Point (Presentation Layer).
 * Provides a console-based UI for Smart City Management.
 *
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#include <iostream>
#include <string>
#include <Domain/TransportService.h>
#include <Domain/PopulationService.h>

using namespace std;

void clearInputBuffer()
{
    cin.ignore(1000000, '\n');
}

void manageTransport(TransportService& service) 
{
    int choice = -1;

    while (choice != 0)
    {
        cout << "\n--- Transport Department ---\n";
        cout << "1. Update Bus Location\n";
        cout << "2. View Bus Route History\n";
        cout << "3. View Scheduled Route\n";
        cout << "4. View Registered Companies\n";
        cout << "5. Register Transport Company\n";
        cout << "6. Register New Bus\n";
        cout << "7. Add New Stop\n";
        cout << "8. Connect Two Stops\n";
        cout << "9. Find Shortest Path\n";

        cout << "0. Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> choice;

        if (cin.fail()) 
        {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1)
        {
            string busId, stopId;
            cout << "Enter Bus ID (e.g., B402): ";
            cin >> busId;
            cout << "Enter New Stop ID (e.g., Stop6): ";
            cin >> stopId;

            if (service.UpdateBusLocation(busId, stopId)) 
            {
                cout << "[Success] Bus location updated.\n";
            }
            else 
            {
                cout << "[Error] Failed to update. Check if Bus ID and Stop ID are valid.\n";
            }
        }
        else if (choice == 2)
        {
            string busId;
            cout << "Enter Bus ID: ";
            cin >> busId;

            const auto* history = service.GetBusRouteHistory(busId);
            if (history)
            {
                cout << "\nRoute History for " << busId << ":\n";

                for (const auto& stop : (*history))
                {
                    cout << " -> " << stop << endl;
                }
            }
            else
            {
                cout << "[Info] No history available or invalid Bus ID.\n";
            }
        }
        else if (choice == 3)
        {
            string busId;
            cout << "Enter Bus ID: ";
            cin >> busId;

            const auto* route = service.GetBusRoute(busId);
            if (route)
            {
                cout << "\nScheduled Route for " << busId << ":\n";

                for (const auto& stop : (*route)) 
                {
                    cout << " - " << stop << endl;
                }
            }
            else 
            {
                cout << "[Info] No route found or invalid Bus ID.\n";
            }
        }
        else if (choice == 4)
        {
            auto* companies = service.GetRegisteredCompanies();
            int i = 1;

            std::cout << '\n';
            for (auto& company : *companies)
            {
                std::cout << "  " << i << ". " << company << '\n';
                i++;
            }
        }
        else if (choice == 5)
        {
            string companyId;
            cout << "Enter Company ID: ";

            clearInputBuffer();
            getline(cin, companyId, '\n');

            if (service.RegisterCompany(companyId))
            {
                cout << "[Success] Company registered.\n";
            }
            else
            {
                cout << "[Error] Failed to register company (might already exist)\n";
            }
        }
        else if (choice == 6)
        {
            string id, company, stopInput;
            LinkedList<string> newRoute;

            cout << "Enter New Bus ID: ";
            cin >> id;
            cout << "Enter Company ID: ";

            clearInputBuffer();
            getline(cin, company);

            cout << "Enter Route Stops (type 'END' to finish):\n";
            while (true)
            {
                cout << "Next Stop ID: ";
                cin >> stopInput;
                if (stopInput == "END") break;
                newRoute.push_back(stopInput);
            }

            if (service.RegisterBus(id, company, newRoute)) 
            {
                cout << "[Success] Bus " << id << " registered successfully.\n";
            }
            else 
            {
                cout << "[Error] Failed. Bus ID might exist, route is empty, or a Stop ID is invalid.\n";
            }
        }
        else if (choice == 7)
        {
            string id, name;
            double lat, lon;

            cout << "Enter Stop ID (e.g., Stop15): ";
            cin >> id;

            cout << "Enter Stop Name (e.g., Central Park): ";

            clearInputBuffer();
            getline(cin, name);

            cout << "Enter Latitude (e.g., 33.684): ";
            cin >> lat;

            cout << "Enter Longitude (e.g., 73.025): ";
            cin >> lon;

            if (service.RegisterStop(id, name, lat, lon))
            {
                cout << "[Success] Stop '" << name << "' registered successfully.\n";
            }
            else
            {
                cout << "[Error] Stop ID already exists.\n";
            }
        }
        else if (choice == 8)
        {
            string src, dest;
            cout << "Enter Source Stop ID: "; cin >> src;
            cout << "Enter Destination Stop ID: "; cin >> dest;

            if (service.AddRoad(src, dest))
                cout << "[Success] Road connected between " << src << " and " << dest << ".\n";
            else
                cout << "[Error] One or both stops do not exist.\n";
        }
        else if (choice == 9)
        {
            string src, dest;
            cout << "Enter Start Stop ID: "; cin >> src;
            cout << "Enter End Stop ID: "; cin >> dest;

            double totalDist = 0.0;
            LinkedList<string> path = service.FindShortestPath(src, dest, totalDist);

            if (!path.empty())
            {
                cout << "\n[Shortest Path Found] Total Distance: " << totalDist << " km\n";
                cout << "Route: ";
                for (auto it = path.begin(); it != path.end(); ++it)
                {
                    cout << *it;
                    auto nextIt = it;
                    if (++nextIt != path.end()) cout << " -> ";
                }
                cout << endl;
            }
            else
            {
                cout << "[Result] No path found between " << src << " and " << dest << ".\n";
            }
        }
    }
}

void managePopulation(PopulationService& service) 
{
    int choice = -1;

    while (choice != 0) 
    {
        cout << "\n--- Population Department ---\n";
        cout << "1. Search Citizen Details\n";
        cout << "2. Register New Sector\n";
        cout << "3. Register New Street\n";
        cout << "4. Register New House\n";

        cout << "0. Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1)
        {
            string cnic;
            cout << "Enter CNIC (without dashes): ";
            cin >> cnic;

            const Person* person = service.GetCitizen(cnic);
            if (person) 
            {
                cout << "\n--- Citizen Record ---\n";
                cout << "Name:       " << person->GetName() << endl;
                cout << "Age:        " << person->GetAge() << endl;
                cout << "Address:    " << person->GetAddress() << endl;
                cout << "Occupation: " << person->GetOccupation() << endl;
                cout << "----------------------\n";
            }
            else 
            {
                cout << "[Result] Citizen not found in database.\n";
            }
        }
        else if (choice == 2) 
        {
            string sectorName;
            cout << "Enter New Sector Name: ";
            cin >> sectorName;

            if (service.RegisterSector(sectorName)) 
            {
                cout << "[Success] Sector '" << sectorName << "' registered.\n";
            }
            else 
            {
                cout << "[Error] Failed to register sector (might already exist).\n";
            }
        }
        else if (choice == 3)
        {
            string streetName;
            string sectorName;

            cout << "Enter the Sector Name: ";
            cin >> sectorName;

            cout << "Enter the Street Name: ";
            cin >> streetName;

            if (service.RegisterStreet(sectorName, streetName))
            {
                cout << "[Success] Street '" << streetName << "' registered.\n";
            }
            else
            {
                cout << "[Error] Failed to register street (either sector does not exist or house already exists).\n";
            }

        }
        else if (choice == 4)
        {
            string houseNo;
            string streetName;
            string sectorName;

            cout << "Enter the Sector Name: ";
            cin >> sectorName;

            cout << "Enter the Street Name: ";
            cin >> streetName;

            cout << "Enter the House Number: ";
            cin >> houseNo;

            if (service.RegisterHouse(sectorName, streetName, houseNo))
            {
                cout << "[Success] House '" << houseNo << "' registered.\n";
            }
            else
            {
                cout << "[Error] Failed to register house (either sector/street does not exist or house already exists).\n";
            }
        }
    }
}

int main()
{
    // 1. Initialize Domain Services
    TransportService transportService;
    PopulationService populationService;

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
            managePopulation(populationService);
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