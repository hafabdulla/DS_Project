#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "../DS_Project/Transport.h"
#include "../DS_Project/Medical.h"
#include "../DS_Project/Population.h"
#include "../DS_Project/Education.h"
#include "../DS_Project/Commercial.h"
#include "../DS_Project/PublicFacilities.h"
#include <iostream>

using namespace std;

class MainMenu {
private:
    TransportModule& transport;
    MedicalModule& medical;
    PopulationModule& population;
    EducationModule& education;
    CommercialModule& commercial;
    PublicFacilitiesModule& facilities;

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pause() {
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    void displayHeader(string title) {
        cout << "\n\n";
        cout << "  " << title;
        for (int i = title.length(); i < 47; i++) cout << " ";
        cout << "\n";
        cout << "\n\n";
    }

    // ==================== TRANSPORT MENU ====================
    void transportMenu() {
        int choice;
        do {
            clearScreen();
            displayHeader("TRANSPORT MANAGEMENT MODULE");
            cout << "[1] Add Bus Stop\n";
            cout << "[2] Connect Two Stops\n";
            cout << "[3] Register New Bus\n";
            cout << "[4] Add Stop to Bus Route\n";
            cout << "[5] Move Bus to Stop\n";
            cout << "[6] Display Bus Route\n";
            cout << "[7] Show Bus Travel History\n";
            cout << "[8] Search Bus by Number\n";
            cout << "[9] List All Buses\n";
            cout << "[10] Display Network Graph\n";
            cout << "[11] Find Shortest Path\n";
            cout << "[12] Manage Passenger Queue\n";
            cout << "[0] Back to Main Menu\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            string stop1, stop2, busNo, company, stopName;
            int distance;

            switch (choice) {
            case 1:
                cout << "Enter stop name: ";
                getline(cin, stopName);
                transport.addBusStop(stopName);
                pause();
                break;

            case 2:
                cout << "Enter first stop: ";
                getline(cin, stop1);
                cout << "Enter second stop: ";
                getline(cin, stop2);
                cout << "Enter distance (km): ";
                cin >> distance;
                transport.connectStops(stop1, stop2, distance);
                pause();
                break;

            case 3:
                cout << "Enter bus number: ";
                getline(cin, busNo);
                cout << "Enter company name: ";
                getline(cin, company);
                transport.registerBus(busNo, company);
                pause();
                break;

            case 4:
                cout << "Enter bus number: ";
                getline(cin, busNo);
                cout << "Enter stop name: ";
                getline(cin, stopName);
                transport.addStopToBus(busNo, stopName);
                pause();
                break;

            case 5:
                cout << "Enter bus number: ";
                getline(cin, busNo);
                cout << "Enter destination stop: ";
                getline(cin, stopName);
                transport.moveBus(busNo, stopName);
                pause();
                break;

            case 6:
                cout << "Enter bus number: ";
                getline(cin, busNo);
                transport.displayBusRoute(busNo);
                pause();
                break;

            case 7:
                cout << "Enter bus number: ";
                getline(cin, busNo);
                transport.showBusHistory(busNo);
                pause();
                break;

            case 8:
                cout << "Enter bus number: ";
                getline(cin, busNo);
                transport.searchBus(busNo);
                pause();
                break;

            case 9:
                transport.listAllBuses();
                pause();
                break;

            case 10:
                transport.displayNetwork();
                pause();
                break;

            case 11:
                cout << "Enter source stop: ";
                getline(cin, stop1);
                cout << "Enter destination stop: ";
                getline(cin, stop2);
                transport.findShortestPath(stop1, stop2);
                pause();
                break;

            case 12:
                cout << "Enter bus number: ";
                getline(cin, busNo);
                transport.managePassengerQueue(busNo);
                break;

            case 0:
                break;

            default:
                cout << "  Invalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }

    // ==================== MEDICAL MENU ====================
    void medicalMenu() {
        int choice;
        do {
            clearScreen();
            displayHeader("MEDICAL SERVICES MODULE");
            cout << "[1] Register Hospital\n";
            cout << "[2] Register Doctor\n";
            cout << "[3] Add Medicine\n";
            cout << "[4] Search Doctor by Specialization\n";
            cout << "[5] Search Medicine by Name\n";
            cout << "[6] Search Medicine by Formula\n";
            cout << "[7] Find Best Emergency Hospital\n";
            cout << "[8] Update Emergency Beds\n";
            cout << "[9] Display Emergency Queue\n";
            cout << "[10] Connect Hospitals\n";
            cout << "[11] Find Nearest Hospital\n";
            cout << "[12] List All Hospitals\n";
            cout << "[13] List All Doctors\n";
            cout << "[0] Back to Main Menu\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            string name, sector, spec, hospital, formula, pharmacy, h1, h2;
            int beds, distance, price;

            switch (choice) {
            case 1:
                cout << "Enter hospital name: ";
                getline(cin, name);
                cout << "Enter sector: ";
                getline(cin, sector);
                cout << "Enter emergency beds: ";
                cin >> beds;
                cin.ignore();
                cout << "Enter specializations: ";
                getline(cin, spec);
                medical.registerHospital(name, sector, beds, spec);
                pause();
                break;

            case 2:
                cout << "Enter doctor name: ";
                getline(cin, name);
                cout << "Enter specialization: ";
                getline(cin, spec);
                cout << "Enter hospital name: ";
                getline(cin, hospital);
                medical.registerDoctor(name, spec, hospital);
                pause();
                break;

            case 3:
                cout << "Enter medicine name: ";
                getline(cin, name);
                cout << "Enter formula: ";
                getline(cin, formula);
                cout << "Enter price: ";
                cin >> price;
                cin.ignore();
                cout << "Enter pharmacy name: ";
                getline(cin, pharmacy);
                medical.addMedicine(name, formula, price, pharmacy);
                pause();
                break;

            case 4:
                cout << "Enter specialization: ";
                getline(cin, spec);
                medical.searchDoctorBySpecialization(spec);
                pause();
                break;

            case 5:
                cout << "Enter medicine name: ";
                getline(cin, name);
                medical.searchMedicineByName(name);
                pause();
                break;

            case 6:
                cout << "Enter formula: ";
                getline(cin, formula);
                medical.searchMedicineByFormula(formula);
                pause();
                break;

            case 7:
                medical.findBestEmergencyHospital();
                pause();
                break;

            case 8:
                cout << "Enter hospital name: ";
                getline(cin, name);
                cout << "Enter new bed count: ";
                cin >> beds;
                medical.updateEmergencyBeds(name, beds);
                pause();
                break;

            case 9:
                medical.displayEmergencyQueue();
                pause();
                break;

            case 10:
                cout << "Enter first hospital: ";
                getline(cin, h1);
                cout << "Enter second hospital: ";
                getline(cin, h2);
                cout << "Enter distance (km): ";
                cin >> distance;
                medical.connectHospitals(h1, h2, distance);
                pause();
                break;

            case 11:
                cout << "Enter source location: ";
                getline(cin, h1);
                cout << "Enter destination hospital: ";
                getline(cin, h2);
                medical.findNearestHospital(h1, h2);
                pause();
                break;

            case 12:
                medical.listAllHospitals();
                pause();
                break;

            case 13:
                medical.listAllDoctors();
                pause();
                break;

            case 0:
                break;

            default:
                cout << "  Invalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }

    // ==================== POPULATION MENU ====================
    void populationMenu() {
        int choice;
        do {
            clearScreen();
            displayHeader("POPULATION & HOUSING MODULE");
            cout << "[1] Add Sector\n";
            cout << "[2] Add Street\n";
            cout << "[3] Add House\n";
            cout << "[4] Register Citizen\n";
            cout << "[5] Search Citizen by CNIC\n";
            cout << "[6] Display City Hierarchy\n";
            cout << "[7] Generate Age Distribution\n";
            cout << "[8] Generate Occupation Summary\n";
            cout << "[9] Generate Gender Ratio\n";
            cout << "[10] List All Citizens\n";
            cout << "[11] Display Family Tree (by House)\n";
            cout << "[12] Generate Family Statistics\n";
            cout << "[0] Back to Main Menu\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            string sector, street, house, cnic, name, occupation, gender;
            int age;

            switch (choice) {
            case 1:
                cout << "Enter sector name: ";
                getline(cin, sector);
                population.addSector(sector);
                pause();
                break;

            case 2:
                cout << "Enter sector name: ";
                getline(cin, sector);
                cout << "Enter street name: ";
                getline(cin, street);
                population.addStreet(sector, street);
                pause();
                break;

            case 3:
                cout << "Enter sector name: ";
                getline(cin, sector);
                cout << "Enter street name: ";
                getline(cin, street);
                cout << "Enter house number: ";
                getline(cin, house);
                population.addHouse(sector, street, house);
                pause();
                break;

            case 4:
                cout << "Enter CNIC: ";
                getline(cin, cnic);
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter occupation: ";
                getline(cin, occupation);
                cout << "Enter sector: ";
                getline(cin, sector);
                cout << "Enter street: ";
                getline(cin, street);
                cout << "Enter house number: ";
                getline(cin, house);
                cout << "Enter gender (M/F): ";
                getline(cin, gender);
                population.registerCitizen(cnic, name, age, occupation, sector, street, house, gender);
                pause();
                break;

            case 5:
                cout << "Enter CNIC: ";
                getline(cin, cnic);
                population.searchByCNIC(cnic);
                pause();
                break;

            case 6:
                population.displayHierarchy();
                pause();
                break;

            case 7:
                population.generateAgeDistribution();
                pause();
                break;

            case 8:
                population.generateOccupationSummary();
                pause();
                break;

            case 9:
                population.generateGenderRatio();
                pause();
                break;

            case 10:
                population.listAllCitizens();
                pause();
                break;
            case 11: {
                cout << "Enter sector name: ";
                getline(cin, sector);
                cout << "Enter street name: ";
                getline(cin, street);
                cout << "Enter house number: ";
                getline(cin, house);
                population.displayFamilyTree(sector, street, house);
                pause();
                break;
            }
            case 12:
                population.generateFamilyStatistics();
                pause();
                break;

            case 0:
                break;

            default:
                cout << "  Invalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }

    // ==================== EDUCATION MENU ====================
    void educationMenu() {
        int choice;
        do {
            clearScreen();
            displayHeader("EDUCATION SYSTEM MODULE");
            cout << "[1] Register School\n";
            cout << "[2] Add Department to School\n";
            cout << "[3] Add Class to Department\n";
            cout << "[4] Display School Hierarchy\n";
            cout << "[5] Search Schools by Subject\n";
            cout << "[6] Display Top Ranked Schools\n";
            cout << "[7] Connect Schools\n";
            cout << "[8] Find Nearest School\n";
            cout << "[9] List All Schools\n";
            cout << "[0] Back to Main Menu\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            string id, name, sector, subjects, dept, className, school1, school2;
            float rating;
            int students, distance;

            switch (choice) {
            case 1:
                cout << "Enter school ID: ";
                getline(cin, id);
                cout << "Enter school name: ";
                getline(cin, name);
                cout << "Enter sector: ";
                getline(cin, sector);
                cout << "Enter rating (0-5): ";
                cin >> rating;
                cin.ignore();
                cout << "Enter subjects (comma-separated): ";
                getline(cin, subjects);
                education.registerSchool(id, name, sector, rating, subjects);
                pause();
                break;

            case 2:
                cout << "Enter school name: ";
                getline(cin, name);
                cout << "Enter department name: ";
                getline(cin, dept);
                education.addDepartment(name, dept);
                pause();
                break;

            case 3:
                cout << "Enter school name: ";
                getline(cin, name);
                cout << "Enter department name: ";
                getline(cin, dept);
                cout << "Enter class name: ";
                getline(cin, className);
                cout << "Enter student count: ";
                cin >> students;
                education.addClass(name, dept, className, students);
                pause();
                break;

            case 4:
                cout << "Enter school name: ";
                getline(cin, name);
                education.displaySchoolHierarchy(name);
                pause();
                break;

            case 5:
                cout << "Enter subject: ";
                getline(cin, subjects);
                education.searchSchoolsBySubject(subjects);
                pause();
                break;

            case 6:
                education.displayTopRankedSchools();
                pause();
                break;

            case 7:
                cout << "Enter first school: ";
                getline(cin, school1);
                cout << "Enter second school: ";
                getline(cin, school2);
                cout << "Enter distance (km): ";
                cin >> distance;
                education.connectSchools(school1, school2, distance);
                pause();
                break;

            case 8:
                cout << "Enter source location: ";
                getline(cin, school1);
                cout << "Enter school name: ";
                getline(cin, school2);
                education.findNearestSchool(school1, school2);
                pause();
                break;

            case 9:
                education.listAllSchools();
                pause();
                break;

            case 0:
                break;

            default:
                cout << "  Invalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }

    // ==================== COMMERCIAL MENU ====================
    void commercialMenu() {
        int choice;
        do {
            clearScreen();
            displayHeader("COMMERCIAL SECTOR MODULE");
            cout << "[1] Register Mall\n";
            cout << "[2] Add Product\n";
            cout << "[3] Search Product by Name\n";
            cout << "[4] Search Products by Category\n";
            cout << "[5] Connect Malls\n";
            cout << "[6] Find Nearest Mall\n";
            cout << "[7] List All Malls\n";
            cout << "[8] List All Products\n";
            cout << "[0] Back to Main Menu\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            string name, sector, productName, category, mallName, mall1, mall2;
            int shops, price, distance;

            switch (choice) {
            case 1:
                cout << "Enter mall name: ";
                getline(cin, name);
                cout << "Enter sector: ";
                getline(cin, sector);
                cout << "Enter number of shops: ";
                cin >> shops;
                commercial.registerMall(name, sector, shops);
                pause();
                break;

            case 2:
                cout << "Enter product name: ";
                getline(cin, productName);
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter price: ";
                cin >> price;
                cin.ignore();
                cout << "Enter mall name: ";
                getline(cin, mallName);
                commercial.addProduct(productName, category, price, mallName);
                pause();
                break;

            case 3:
                cout << "Enter product name: ";
                getline(cin, productName);
                commercial.searchProductByName(productName);
                pause();
                break;

            case 4:
                cout << "Enter category: ";
                getline(cin, category);
                commercial.searchProductsByCategory(category);
                pause();
                break;

            case 5:
                cout << "Enter first mall: ";
                getline(cin, mall1);
                cout << "Enter second mall: ";
                getline(cin, mall2);
                cout << "Enter distance (km): ";
                cin >> distance;
                commercial.connectMalls(mall1, mall2, distance);
                pause();
                break;

            case 6:
                cout << "Enter source location: ";
                getline(cin, mall1);
                cout << "Enter mall name: ";
                getline(cin, mall2);
                commercial.findNearestMall(mall1, mall2);
                pause();
                break;

            case 7:
                commercial.listAllMalls();
                pause();
                break;

            case 8:
                commercial.listAllProducts();
                pause();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }

    // ==================== PUBLIC FACILITIES MENU ====================
    void facilitiesMenu() {
        int choice;
        do {
            clearScreen();
            displayHeader("PUBLIC FACILITIES MODULE");
            cout << "[1] Register Facility\n";
            cout << "[2] Search Facility by Name\n";
            cout << "[3] Search Facilities by Type\n";
            cout << "[4] Connect Facilities\n";
            cout << "[5] Find Nearest Facility\n";
            cout << "[6] Find Nearest Facility by Type\n";
            cout << "[7] Display Facility Network\n";
            cout << "[8] List All Facilities\n";
            cout << "[9] List Facilities by Sector\n";
            cout << "[10] Generate Facility Report\n";
            cout << "[0] Back to Main Menu\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            string name, sector, type, fac1, fac2;
            int capacity, distance;
            string hours;

            switch (choice) {
            case 1:
                cout << "Enter facility name: ";
                getline(cin, name);
                cout << "Enter sector: ";
                getline(cin, sector);
                cout << "Enter type (Park/Library/Sports Complex/etc): ";
                getline(cin, type);
                cout << "Enter capacity: ";
                cin >> capacity;
                cin.ignore();
                cout << "Enter opening hours: ";
                getline(cin, hours);
                facilities.registerFacility(name, sector, type, capacity, hours);
                pause();
                break;

            case 2:
                cout << "Enter facility name: ";
                getline(cin, name);
                facilities.searchFacilityByName(name);
                pause();
                break;

            case 3:
                cout << "Enter facility type: ";
                getline(cin, type);
                facilities.searchFacilitiesByType(type);
                pause();
                break;

            case 4:
                cout << "Enter first facility: ";
                getline(cin, fac1);
                cout << "Enter second facility: ";
                getline(cin, fac2);
                cout << "Enter distance (km): ";
                cin >> distance;
                facilities.connectFacilities(fac1, fac2, distance);
                pause();
                break;

            case 5:
                cout << "Enter source location: ";
                getline(cin, fac1);
                cout << "Enter facility name: ";
                getline(cin, fac2);
                facilities.findNearestFacility(fac1, fac2);
                pause();
                break;

            case 6:
                cout << "Enter source location: ";
                getline(cin, fac1);
                cout << "Enter facility type: ";
                getline(cin, type);
                facilities.findNearestFacilityOfType(fac1, type);
                pause();
                break;

            case 7:
                facilities.displayFacilityNetwork();
                pause();
                break;

            case 8:
                facilities.listAllFacilities();
                pause();
                break;

            case 9:
                cout << "Enter sector: ";
                getline(cin, sector);
                facilities.listFacilitiesBySector(sector);
                pause();
                break;

            case 10:
                facilities.generateFacilityReport();
                pause();
                break;

            case 0:
                break;

            default:
                cout << "  Invalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }

    // ==================== REPORTS MENU ====================
    void reportsMenu() {
        int choice;
        do {
            clearScreen();
            displayHeader("SYSTEM REPORTS & ANALYTICS");
            cout << "[1] Population Age Distribution\n";
            cout << "[2] Occupation Summary\n";
            cout << "[3] Gender Ratio Report\n";
            cout << "[4] Public Facilities Report\n";
            cout << "[5] Emergency Hospital Rankings\n";
            cout << "[6] Top Ranked Schools\n";
            cout << "[7] All Registered Buses\n";
            cout << "[8] All Registered Citizens\n";
            cout << "[0] Back to Main Menu\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                population.generateAgeDistribution();
                pause();
                break;

            case 2:
                population.generateOccupationSummary();
                pause();
                break;

            case 3:
                population.generateGenderRatio();
                pause();
                break;

            case 4:
                facilities.generateFacilityReport();
                pause();
                break;

            case 5:
                medical.displayEmergencyQueue();
                pause();
                break;

            case 6:
                education.displayTopRankedSchools();
                pause();
                break;

            case 7:
                transport.listAllBuses();
                pause();
                break;

            case 8:
                population.listAllCitizens();
                pause();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }

public:
    MainMenu(TransportModule& t, MedicalModule& m, PopulationModule& p,
        EducationModule& e, CommercialModule& c, PublicFacilitiesModule& f)
        : transport(t), medical(m), population(p), education(e), commercial(c), facilities(f) {
    }

    void displayMainMenu() {
        int choice;
        do {
            clearScreen();
            cout << "\n\n";
            cout << "         SMART CITY MANAGEMENT SYSTEM               \n";
            cout << "              Islamabad - Pakistan                  \n";
            cout << "         Data Structures Project 2025               \n";
            cout << "\n";
            cout << "\n[1] Transport Management\n";
            cout << "[2] Medical Services\n";
            cout << "[3] Population & Housing\n";
            cout << "[4] Education System\n";
            cout << "[5] Commercial Sector\n";
            cout << "[6] Public Facilities\n";
            cout << "[7] Generate Reports\n";
            cout << "[0] Exit System\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                transportMenu();
                break;
            case 2:
                medicalMenu();
                break;
            case 3:
                populationMenu();
                break;
            case 4:
                educationMenu();
                break;
            case 5:
                commercialMenu();
                break;
            case 6:
                facilitiesMenu();
                break;
            case 7:
                reportsMenu();
                break;
            case 0:
                clearScreen();
                cout << "\n\n";
                cout << "               System Shutdown Complete              \n";
                cout << "            Thank you for using Smart City!          \n";
                cout << "\n\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
                pause();
            }
        } while (choice != 0);
    }
};

#endif // MAINMENU_H