#include <Domain/TransportService.h>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void clearInputBuffer();

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
        cout << "10. Find Nearest Bus\n";

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
        else if (choice == 10)
        {
            double lat, lon;
            cout << "Enter Your Latitude: "; cin >> lat;
            cout << "Enter Your Longitude: "; cin >> lon;

            string nearestBusID;
            double distance = 0.0;

            if (service.FindNearestBus(lat, lon, nearestBusID, distance))
            {
                cout << "\n[Result] Nearest Bus found!\n";
                cout << "Bus ID:   " << nearestBusID << "\n";
                cout << "Distance: " << distance << " km away\n";
            }
            else
            {
                cout << "[Result] No buses available or bus stops not found in network.\n";
            }
        }
    }
}