#pragma once
#ifndef DATALOADER_H
#define DATALOADER_H

#include "../DS_Project/CSVParser.h"
#include "../DS_Project/Transport.h"
#include "../DS_Project/Medical.h"
#include "../DS_Project/Population.h"
#include "../DS_Project/Education.h"
#include "../DS_Project/Commercial.h"
#include "../DS_Project/PublicFacilities.h"
#include <fstream>
#include <iostream>
using namespace std;

class DataLoader {
public:


    static bool loadBuses(const string& filename, TransportModule& transport) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }

        string line;
        getline(file, line);

        int count = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string tokens[10];
            int tokenCount = CSVParser::parseLine(line, tokens, 10);

            if (tokenCount >= 4) {
                string busNo = tokens[0];
                string company = tokens[1];
                string currentStop = tokens[2];
                string route = tokens[3];

                // Register bus
                transport.registerBus(busNo, company);

                // Parse route (Stop1 > Stop2 > Stop3)
                string stops[20];
                int stopCount = 0;
                string current = "";

                for (int i = 0; i < route.length(); i++) {
                    if (route[i] == '>') {
                        stops[stopCount++] = CSVParser::trim(current);
                        current = "";
                    }
                    else {
                        current += route[i];
                    }
                }
                if (current.length() > 0) {
                    stops[stopCount++] = CSVParser::trim(current);
                }

                // Add stops to bus route
                for (int i = 0; i < stopCount; i++) {
                    transport.addStopToBus(busNo, stops[i]);
                }

                // Move bus to current stop
                transport.moveBus(busNo, currentStop);
                count++;
            }
        }

        file.close();
        cout << "  Loaded " << count << " buses from " << filename << endl;
        return true;
    }

    // Load bus stops from CSV
    static bool loadStops(const string& filename, TransportModule& transport) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }

        string line;
        getline(file, line);

        int count = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string tokens[10];
            int tokenCount = CSVParser::parseLine(line, tokens, 10);

            if (tokenCount >= 2) {
                string stopID = tokens[0];
                string name = tokens[1];
                // Coordinates in tokens[2]

                transport.addBusStop(name);
                count++;
            }
        }

        file.close();
        cout << "  Loaded " << count << " bus stops from " << filename << endl;
        return true;
    }

    
    static bool loadSchools(const string& filename, EducationModule& education) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }

        string line;
        getline(file, line);


        int count = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string tokens[10];
            int tokenCount = CSVParser::parseLine(line, tokens, 10);

            if (tokenCount >= 5) {
                string schoolID = tokens[0];
                string name = tokens[1];
                string sector = tokens[2];
                float rating = CSVParser::toFloat(tokens[3]);
                string subjects = tokens[4];

                education.registerSchool(schoolID, name, sector, rating, subjects);
                count++;
            }
        }

        file.close();
        cout << "  Loaded " << count << " schools from " << filename << endl;
        return true;
    }

    static bool loadHospitals(const string& filename, MedicalModule& medical) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }

        string line;
        getline(file, line); 

        int count = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string tokens[10];
            int tokenCount = CSVParser::parseLine(line, tokens, 10);

            if (tokenCount >= 5) {
                string hospitalID = tokens[0];
                string name = tokens[1];
                string sector = tokens[2];
                int beds = CSVParser::toInt(tokens[3]);
                string specialization = tokens[4];

                medical.registerHospital(name, sector, beds, specialization);
                count++;
            }
        }

        file.close();
        cout << "Loaded " << count << " hospitals from " << filename << endl;
        return true;
    }


    static bool loadPharmacies(const string& filename, MedicalModule& medical) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }

        string line;
        getline(file, line); 

        int count = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string tokens[10];
            int tokenCount = CSVParser::parseLine(line, tokens, 10);

            if (tokenCount >= 6) {
                string pharmacyID = tokens[0];
                string pharmacyName = tokens[1];
                string sector = tokens[2];
                string medicineName = tokens[3];
                string formula = tokens[4];
                int price = CSVParser::toInt(tokens[5]);

                medical.addMedicine(medicineName, formula, price, pharmacyName);
                count++;
            }
        }

        file.close();
        cout << "Loaded " << count << " medicines from " << filename << endl;
        return true;
    }


    static bool loadPopulation(const string& filename, PopulationModule& population) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }

        string line;
        getline(file, line);

        int count = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string tokens[10];
            int tokenCount = CSVParser::parseLine(line, tokens, 10);

            if (tokenCount >= 7) {
                string cnic = tokens[0];
                string name = tokens[1];
                int age = CSVParser::toInt(tokens[2]);
                string sector = tokens[3];
                string street = tokens[4];
                string houseNo = tokens[5];
                string occupation = tokens[6];


                string relation = "Head";
                string gender = "M";

                if (age < 18) {
                    relation = "Child";
                }
                else if (age >= 18 && age < 45) {
                    // Could be parent or child
                    if (count % 3 == 1) relation = "Spouse";
                }


                if (name.find("Fatima") != string::npos || name.find("Sara") != string::npos) {
                    gender = "F";
                    if (relation == "Head") relation = "Mother";
                }

                population.registerCitizen(cnic, name, age, occupation,
                    sector, street, houseNo, gender, relation);
                count++;
            }
        }

        file.close();
        cout << "Loaded " << count << " citizens with family relationships\n";
        return true;
    }

    static void loadAllData(TransportModule& transport, MedicalModule& medical,
        PopulationModule& population, EducationModule& education,
        CommercialModule& commercial, PublicFacilitiesModule& facilities) {

        cout << "\n========================================\n";
        cout << "   LOADING DATA FROM CSV FILES\n";
        cout << "========================================\n\n";


        cout << "--- Transport Module ---\n";
        loadStops("stops.csv", transport);
        loadBuses("buses.csv", transport);


        cout << "\n--- Connecting Bus Stops ---\n";
        transport.connectStops("G-10 Markaz", "F-10 Park", 3);
        transport.connectStops("F-10 Park", "PIMS Hospital", 4);
        transport.connectStops("PIMS Hospital", "F-8 Kacheri", 2);
        transport.connectStops("F-8 Kacheri", "G-9 Bus Adda", 3);
        transport.connectStops("G-9 Bus Adda", "Blue Area", 5);
        transport.connectStops("Blue Area", "Centaurus", 2);
        transport.connectStops("Centaurus", "Faisal Mosque", 4);
        transport.connectStops("Faisal Mosque", "Lake View", 8);
        transport.connectStops("Lake View", "F-7 Jinnah", 6);
        transport.connectStops("F-7 Jinnah", "F-6 Super", 3);
        cout << "Connected 10 bus stop routes\n";


        cout << "\n--- Medical Module ---\n";
        loadHospitals("hospitals.csv", medical);
        loadPharmacies("pharmacies.csv", medical);


        cout << "\n--- Adding Doctors ---\n";
        medical.registerDoctor("Dr. Ahmed Khan", "General", "PIMS");
        medical.registerDoctor("Dr. Fatima Ali", "Cardiology", "PIMS");
        medical.registerDoctor("Dr. Hassan Raza", "Oncology", "Shifa International");
        medical.registerDoctor("Dr. Sara Malik", "Surgery", "Shifa International");
        medical.registerDoctor("Dr. Ali Noor", "Orthopedics", "Maroof Hospital");
        cout << "Added 5 doctors\n";


        cout << "\n--- Connecting Hospitals ---\n";
        medical.connectHospitals("PIMS", "Shifa International", 8);
        medical.connectHospitals("Shifa International", "Maroof Hospital", 6);
        medical.connectHospitals("Maroof Hospital", "Poly Clinic", 5);
        medical.connectHospitals("Poly Clinic", "Islamabad Medical", 7);
        cout << "Connected hospital network\n";


        cout << "\n--- Education Module ---\n";
        loadSchools("schools.csv", education);


        cout << "\n--- Building School Hierarchies ---\n";
        education.addDepartment("City School", "Science");
        education.addDepartment("City School", "Arts");
        education.addClass("City School", "Science", "Class 9-A", 35);
        education.addClass("City School", "Science", "Class 10-A", 32);
        education.addClass("City School", "Arts", "Class 9-B", 28);

        education.addDepartment("Allied School", "Computer Science");
        education.addDepartment("Allied School", "Mathematics");
        education.addClass("Allied School", "Computer Science", "CS-1A", 30);
        education.addClass("Allied School", "Mathematics", "Math-9A", 25);

        education.addDepartment("Beaconhouse", "Sciences");
        education.addClass("Beaconhouse", "Sciences", "Bio-10A", 28);

        cout << "Created 3 school hierarchies\n";

        cout << "\n--- Connecting Schools ---\n";
        education.connectSchools("City School", "Allied School", 5);
        education.connectSchools("Allied School", "Beaconhouse", 7);
        cout << "Connected school network\n";


        cout << "\n--- Population Module ---\n";


        cout << "Creating city hierarchy...\n";
        population.addSector("G-10");
        population.addSector("F-8");
        population.addSector("G-9");
        population.addSector("F-6");
        population.addSector("Blue Area");

        population.addStreet("G-10", "22");
        population.addStreet("F-8", "5");
        population.addStreet("G-9", "17");
        population.addStreet("F-6", "9");
        population.addStreet("Blue Area", "1");

        population.addHouse("G-10", "22", "180");
        population.addHouse("F-8", "5", "12");
        population.addHouse("G-9", "17", "90");
        population.addHouse("F-6", "9", "33");
        population.addHouse("Blue Area", "1", "5");

        cout << "Created city hierarchy\n";

        loadPopulation("population.csv", population);


        cout << "\n--- Commercial Module ---\n";
        commercial.registerMall("Centaurus Mall", "F-8", 150);
        commercial.registerMall("Giga Mall", "DHA-2", 200);
        commercial.registerMall("Safa Gold Mall", "F-7", 80);

        commercial.addProduct("Samsung S24", "Electronics", 189000, "Centaurus Mall");
        commercial.addProduct("iPhone 15", "Electronics", 350000, "Centaurus Mall");
        commercial.addProduct("Nike Shoes", "Fashion", 12000, "Giga Mall");
        commercial.addProduct("Adidas Sneakers", "Fashion", 15000, "Giga Mall");
        commercial.addProduct("Sony Headphones", "Electronics", 25000, "Safa Gold Mall");

        commercial.connectMalls("Centaurus Mall", "Giga Mall", 12);
        commercial.connectMalls("Giga Mall", "Safa Gold Mall", 8);
        cout << "Loaded malls with products\n";

        // Public Facilities (sample)
        cout << "\n--- Public Facilities Module ---\n";
        facilities.registerFacility("F-9 Park", "F-9", "Park", 500, "6 AM - 10 PM");
        facilities.registerFacility("Fatima Jinnah Park", "F-9", "Park", 1000, "24 Hours");
        facilities.registerFacility("Central Library", "G-6", "Library", 200, "9 AM - 6 PM");
        facilities.registerFacility("Sports Complex", "G-9", "Sports Complex", 300, "6 AM - 9 PM");
        facilities.registerFacility("Aabpara Police Station", "G-6", "Police Station", 50, "24 Hours");
        cout << "Loaded public facilities\n";
        ;
    }
};

#endif // DATALOADER_H
