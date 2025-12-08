#pragma once
#ifndef PUBLIC_FACILITIES_H
#define PUBLIC_FACILITIES_H

#include "../DS_Project/Graph.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/LinkedList.h"
#include <iostream>
using namespace std;

string FacilityType(const string& type) {
    string t = type;
    for (char& c : t) c = tolower(c);

    if (t == "park") return "Park";
    if (t == "library") return "Library";
    if (t == "community center") return "Community Center";
    if (t == "sports complex") return "Sports Complex";
    if (t == "police station") return "Police Station";
    if (t == "post office") return "Post Office";

    return "Unknown";
}

class PublicFacility {
public:
    string facilityName;
    string sector;
    string type;
    int capacity;
    string openingHours;

    PublicFacility(string name, string sec, string t, int cap, string hours)
        : facilityName(name),
        sector(sec),
        type(FacilityType(t)),
        capacity(cap),
        openingHours(hours) {
    }

    string toString() {
        return facilityName + "|" + sector + "|" + type +
            "|" + to_string(capacity) + "|" + openingHours;
    }
};

class PublicFacilitiesModule {
private:
    Graph facilityNetwork;
    HashTable facilityRegistry;
    HashTable facilitiesByType;

    PublicFacility* facilities[200];
    int facilityCount;

    void parseFacilityData(string data) {
        string tokens[5];
        int tokenCount = 0;
        string temp = "";

        for (int i = 0; i < data.length(); i++) {
            if (data[i] == '|') {
                tokens[tokenCount++] = temp;
                temp = "";
            }
            else {
                temp += data[i];
            }
        }
        tokens[tokenCount++] = temp;

        if (tokenCount >= 5) {
            cout << "Facility: " << tokens[0] << "\n";
            cout << "Sector: " << tokens[1] << "\n";
            cout << "Type: " << tokens[2] << "\n";
            cout << "Capacity: " << tokens[3] << "\n";
            cout << "Hours: " << tokens[4] << "\n";
        }
    }

public:
    PublicFacilitiesModule() : facilityCount(0) {
        for (int i = 0; i < 200; i++) facilities[i] = nullptr;
    }

    ~PublicFacilitiesModule() {
        for (int i = 0; i < facilityCount; i++) delete facilities[i];
    }
    void registerFacility(string name, string sector, string type, int capacity, string hours) {
        if (facilityCount >= 200) {
            cout << "Facility limit reached!\n";
            return;
        }

        string fixedType = FacilityType(type);
        PublicFacility* newFacility = new PublicFacility(name, sector, fixedType, capacity, hours);
        facilities[facilityCount++] = newFacility;


        facilityRegistry.insert(name, newFacility->toString());

        string existing = facilitiesByType.search(fixedType);
        if (existing == "") {
            facilitiesByType.insert(fixedType, name + "@" + sector);
        }
        else {
            facilitiesByType.insert(fixedType, existing + ";" + name + "@" + sector);
        }

        facilityNetwork.addVertex(name);

        cout << "Registered: " << name << " (" << fixedType << ") in " << sector << "\n";
    }

    void searchFacilityByName(string name) {
        string data = facilityRegistry.search(name);
        if (data != "") {
            cout << "\n=== Facility Found (Hash O(1)) ===\n";
            parseFacilityData(data);
        }
        else {
            cout << "Facility '" << name << "' not found!\n";
        }
    }

    void searchFacilitiesByType(string type) {
        string fixedType = FacilityType(type);
        string result = facilitiesByType.search(fixedType);

        if (result == "") {
            cout << "No facilities found of type: " << fixedType << "\n";
            return;
        }

        cout << "\n=== Facilities of Type: " << fixedType << " ===\n";

        string current = "";
        int count = 1;
        for (int i = 0; i < result.length(); i++) {
            if (result[i] == ';') {
                int atPos = current.find('@');
                if (atPos != string::npos) {
                    string facName = current.substr(0, atPos);
                    string sec = current.substr(atPos + 1);
                    cout << count++ << ". " << facName << " (" << sec << ")\n";
                }
                current = "";
            }
            else {
                current += result[i];
            }
        }

        if (current != "") {
            int atPos = current.find('@');
            if (atPos != string::npos) {
                string facName = current.substr(0, atPos);
                string sec = current.substr(atPos + 1);
                cout << count << ". " << facName << " (" << sec << ")\n";
            }
        }
    }

    void connectFacilities(string facility1, string facility2, int distance) {
        facilityNetwork.addEdge(facility1, facility2, distance);
    }

    void findNearestFacility(string source, string destination) {
        cout << "Finding Nearest Facility Route (Dijkstra)\n";
        facilityNetwork.FindShortestPath(source, destination);
    }

    void displayFacilityNetwork() {
        cout << "Public Facilities Network\n";
        facilityNetwork.display();
    }

    void listAllFacilities() {
        if (facilityCount == 0) {
            cout << "No facilities registered.\n";
            return;
        }

        cout << "All Public Facilities\n";
        for (int i = 0; i < facilityCount; i++) {
            cout << (i + 1) << ". " << facilities[i]->facilityName
                << " (" << facilities[i]->type << ") - "
                << facilities[i]->sector << "\n";
        }
    }

    void listFacilitiesBySector(string sector) {
        cout << "Facilities in " << sector << "\n";
        bool found = false;

        for (int i = 0; i < facilityCount; i++) {
            if (facilities[i]->sector == sector) {
                cout << "• " << facilities[i]->facilityName
                    << " (" << facilities[i]->type << ")\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No facilities found in sector: " << sector << "\n";
        }
    }

    void generateFacilityReport() {
        if (facilityCount == 0) {
            cout << "No facilities to report.\n";
            return;
        }

        int parks = 0, libraries = 0, centers = 0, sports = 0, police = 0, post = 0;

        for (int i = 0; i < facilityCount; i++) {
            string t = facilities[i]->type;

            if (t == "Park") parks++;
            else if (t == "Library") libraries++;
            else if (t == "Community Center") centers++;
            else if (t == "Sports Complex") sports++;
            else if (t == "Police Station") police++;
            else if (t == "Post Office") post++;
        }

        cout << "Public Facilities Report\n";
        cout << "Total Facilities: " << facilityCount << "\n\n";
        cout << "Breakdown by Type:\n";
        cout << "Parks: " << parks << "\n";
        cout << "Libraries: " << libraries << "\n";
        cout << "Community Centers: " << centers << "\n";
        cout << "Sports Complexes: " << sports << "\n";
        cout << "Police Stations: " << police << "\n";
        cout << "Post Offices: " << post << "\n";
    }

    void findNearestFacilityOfType(string fromLocation, string type) {
        string fixedType = FacilityType(type);

        cout << "\n=== Finding Nearest " << fixedType << " ===\n";

        bool found = false;
        for (int i = 0; i < facilityCount; i++) {
            if (facilities[i]->type == fixedType) {
                cout << "Checking path to: " << facilities[i]->facilityName << "\n";
                facilityNetwork.FindShortestPath(fromLocation, facilities[i]->facilityName);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No " << fixedType << " facilities registered.\n";
        }
    }
};
#endif