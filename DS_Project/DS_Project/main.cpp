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
#include "../DS_Project/Medical.h"
#include "../DS_Project/Education.h"
#include "../DS_Project/Commercial.h"
#include "../DS_Project/PublicFacilities.h"
#include "../DS_Project/CSVParser.h"
#include "../DS_Project/DataLoader.h"
#include "MainMenu.h"

using namespace std;

int main() {

    cout << "         SMART CITY MANAGEMENT SYSTEM\n";
    cout << "              Islamabad - Pakistan\n";
    cout << "         Data Structures Project 2025\n";


    TransportModule transport;
    MedicalModule medical;
    PopulationModule population;
    EducationModule education;
    CommercialModule commercial;
    PublicFacilitiesModule facilities;

    cout << "\nDo you want to load data from CSV files? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();

    if (choice == 'y' || choice == 'Y') {
        DataLoader::loadAllData(transport, medical, population, education, commercial, facilities);
        cout << "\nPress Enter to continue to main menu...";
        cin.get();
    }
    else {
        cout << "Starting with empty system";
    }



    MainMenu mainMenu(transport, medical, population, education, commercial, facilities);
    mainMenu.displayMainMenu();


    cout << "              System Shutdown Complete\n";
    cout << "           Thank you for using Smart City!\n";


    return 0;
}