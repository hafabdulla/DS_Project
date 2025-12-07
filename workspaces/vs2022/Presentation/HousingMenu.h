#include <iostream>
#include <string>
#include <Domain/HousingService.h>

using namespace std;

void clearInputBufferac();

void managePopulation(HousingService& service)
{
    int choice = -1;

    while (choice != 0)
    {
        cout << "\n--- Population Department ---\n";
        cout << "1. Search Citizen Details\n";
        cout << "2. Register New Sector\n";
        cout << "3. Register New Street\n";
        cout << "4. Register New House\n";
        cout << "5. Register New Family\n";
        cout << "6. Register New Individual\n";
        cout << "7. View Population Hierarchy\n";
        cout << "8. View Age Distribution Report\n";
        cout << "9. View Occupation Summary\n";
        cout << "10. Find Residents of Sector\n";

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

        switch(choice)
        {

        case 1:
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

            break;
        }

        case 2:
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
            
            break;
        }

        case 3:
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

            break;
        }

        case 4:
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

            break;
        }

        case 5:
        {
            string sector, street, house, family;
            cout << "Enter Sector: "; cin >> sector;
            cout << "Enter Street: "; cin >> street;
            cout << "Enter House No: "; cin >> house;

            cout << "Enter Family Name (e.g., KhanFamily): ";
            cin >> family;

            if (service.RegisterFamily(sector, street, house, family))
                cout << "[Success] Family '" << family << "' registered.\n";
            else
                cout << "[Error] Failed. House might not exist or family already registered.\n";

            break;
        }

        case 6:
        {
            string sector, street, house, family;
            string cnic, name, occupation;
            int age;

            cout << "--- Location Info ---\n";
            cout << "Enter Sector: ";
            cin >> sector;

            cout << "Enter Street: ";
            cin >> street;

            cout << "Enter House No: ";
            cin >> house;

            cout << "Enter Family Name: ";
            cin >> family;

            cout << "--- Personal Info ---\n";
            cout << "Enter CNIC (unique): ";
            cin >> cnic;

            cout << "Enter Name: ";

            clearInputBuffer();
            getline(cin, name);

            cout << "Enter Age: ";
            cin >> age;

            cout << "Enter Occupation: ";
            cin >> occupation;

            string address = "House " + house + ", Street " + street + ", " + sector;

            Person newPerson(cnic, name, age, address, occupation);

            if (service.RegisterIndividual(sector, street, house, family, newPerson))
                cout << "[Success] Citizen registered successfully.\n";
            else
                cout << "[Error] Failed. Family not found or CNIC already exists.\n";
            
            break;
        }

        case 7:
        {
            cout << "\n--- Islamabad City Hierarchy ---\n";

            auto printNode = [](const string& key, const string& val)
                {
                    size_t depth = 0;
                    for (char c : key)
                    {
                        if (c == ':')
                            depth++;
                    }

                    string indent(depth * 3, ' ');
                    string displayName = val;
                    size_t lastColon = val.find_last_of(':');
                    if (lastColon != string::npos)
                    {
                        displayName = val.substr(lastColon + 1);
                    }

                    cout << indent << "|__ " << displayName << endl;
                };

            service.TraverseHousingHierarchy(printNode);

            break;
        }

        case 8:
        {
            int child, young, adult, senior;
            service.GetAgeDistribution(child, young, adult, senior);

            int total = child + young + adult + senior;
            if (total == 0) total = 1;

            cout << "\n--- Age Distribution Report ---\n";
            cout << "Children (0-18): " << child << " (" << (child * 100 / total) << "%)\n";
            cout << "Youth (19-35):   " << young << " (" << (young * 100 / total) << "%)\n";
            cout << "Adults (36-60):  " << adult << " (" << (adult * 100 / total) << "%)\n";
            cout << "Seniors (60+):   " << senior << " (" << (senior * 100 / total) << "%)\n";

            break;
        }

        case 9:
        {
            cout << "\n--- Occupation Summary ---\n";

            auto printJob = [](const string& job, int count)
                {
                    cout << "- " << job << ": " << count << endl;
                };

            service.TraverseOccupationSummary(printJob);

            break;
        }

        case 10:
        {
            string sector;
            cout << "Enter Sector Name (e.g., G-10): ";
            cin >> sector;

            LinkedList<const Person*> residents;
            service.GetResidentsInSector(sector, residents);

            if (residents.empty())
            {
                cout << "[Result] No residents found in " << sector << " (or sector does not exist).\n";
            }
            else
            {
                cout << "\n--- Residents of " << sector << " ---\n";
                int count = 0;
                for (const Person* p : residents)
                {
                    cout << ++count << ". " << p->GetName()
                        << " (" << p->GetOccupation() << ") - "
                        << p->GetAddress() << endl;
                }
                cout << "-----------------------------\n";
                cout << "Total: " << count << " residents.\n";
            }

            break;
        }

        default:
            break;
        }
    }
}