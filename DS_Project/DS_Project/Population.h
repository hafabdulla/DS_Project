#pragma once
#ifndef POPULATION_H
#define POPULATION_H

#include "../DS_Project/Tree.h"
#include "../DS_Project/HashTable.h"
#include <iostream>
using namespace std;

class Citizen {
public:
	string CNIC;
	string name;
	int age;
	string Occupation;
	string address;
	string gender;

	Citizen(string C, string N, int A, string O, string Ad, string g = "M"):CNIC (C), name(N), age(A), Occupation(O), address(Ad), gender(g){	}
	string toString() {
		return name + " | " + to_string(age) + " | " + Occupation + " | " + address + " | " + gender;
	}
};

class PopulationModule {
private:
	Tree* cityHierarchy;
	HashTable citizenRegistry;
	Citizen* citizens[1000];
	int citizenCount;
public:
	PopulationModule() :citizenCount(0) {
		cityHierarchy = new Tree("Islamabad");
		for (int i = 0; i < 1000; i++)
		{
			citizens[i] = nullptr;
		}
	}

	~PopulationModule() {
		delete cityHierarchy;
		for (int i = 0; i < citizenCount; i++)
		{
			delete citizens[i];
		}
	}
	//Hierarchy
	void addSector(string SectorName) {
		TreeNode* sector = new TreeNode(SectorName);
		cityHierarchy->getRoot()->addChild(sector);
		cout << "Sector: " << SectorName << " Added\n";
	}

	void addStreet(string sectorName, string streetName) {
		TreeNode* sector = cityHierarchy->search(cityHierarchy->getRoot(), sectorName);
		if (sector != nullptr) {
			TreeNode* street = new TreeNode(streetName);
			sector->addChild(street);
			cout << "Street: " << streetName << " to: " << sectorName << "\n";
		}else{
			cout << "Sector: " << sectorName << " not found!\n";
		}
	}

	void addHouse(string sectorName, string streetName, string houseNumber) {
		TreeNode* sector = cityHierarchy->search(cityHierarchy->getRoot(), sectorName);
		if (sector != nullptr) {
			TreeNode* street = cityHierarchy->search(sector, streetName);
			if (street != nullptr) {
				TreeNode* house = new TreeNode("House " + houseNumber);
				street->addChild(house);
				cout << "Added House: " << houseNumber << " to " << sectorName << "/" << streetName << "\n";
			}
			else {
				cout << "Street: '" << streetName << "' not found!\n";
			}
		}
		else {
			cout << "Sector '" << sectorName << "' not found!\n";
		}
	}

	void displayHierarchy() {
		cout << "\n=== Islamabad City Hierarchy ===\n";
		cityHierarchy->display();
	}

	void registerCitizen(string cnic, string name, int age, string occupation,
		string sector, string street, string houseNo, string gender = "M") {
		if (citizenCount >= 1000) {
			cout << "Citizen limit reached!\n";
			return;
		}

		// duplication check
		if (citizenRegistry.search(cnic) != "") {
			cout << "Citizen with CNIC " << cnic << " already registered!\n";
			return;
		}

		string address = sector + ", Street " + street + ", House " + houseNo;
		Citizen* newCitizen = new Citizen(cnic, name, age, occupation, address, gender);

		citizens[citizenCount++] = newCitizen;
		citizenRegistry.insert(cnic, newCitizen->toString());

		cout << "Registered: " << name << " (CNIC: " << cnic << ")\n";
	}

	void searchByCNIC(string cnic) {
		string data = citizenRegistry.search(cnic);
		if (data != "") {
			cout << "\n--- Citizen Found (O(1) Hash Lookup) ---\n";
			cout << "CNIC: " << cnic << "\n";


			string tokens[10];
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

			if (tokenCount >= 4) {
				cout << "Name: " << tokens[0] << "\n";
				cout << "Age: " << tokens[1] << "\n";
				cout << "Occupation: " << tokens[2] << "\n";
				cout << "Address: " << tokens[3] << "\n";
				if (tokenCount >= 5) {
					cout << "Gender: " << tokens[4] << "\n";
				}
			}
		}
		else {
			cout << "Citizen with CNIC " << cnic << " not found!\n";
		}
	}

	void generateAgeDistribution() {
		if (citizenCount == 0) {
			cout << "\nNo citizens registered.\n";
			return;
		}

		int age0_18 = 0, age19_35 = 0, age36_60 = 0, age60plus = 0;

		for (int i = 0; i < citizenCount; i++) {
			int age = citizens[i]->age;
			if (age <= 18) age0_18++;
			else if (age <= 35) age19_35++;
			else if (age <= 60) age36_60++;
			else age60plus++;
		}

		cout << "\n=== UC-H7: Age Distribution Report ===\n";
		cout << "Total Population: " << citizenCount << "\n";
		cout << "0-18 years:   " << age0_18 << " (" << (age0_18 * 100 / citizenCount) << "%)\n";
		cout << "19-35 years:  " << age19_35 << " (" << (age19_35 * 100 / citizenCount) << "%)\n";
		cout << "36-60 years:  " << age36_60 << " (" << (age36_60 * 100 / citizenCount) << "%)\n";
		cout << "60+ years:    " << age60plus << " (" << (age60plus * 100 / citizenCount) << "%)\n";
	}

	void generateOccupationSummary() {
		if (citizenCount == 0) {
			cout << "\nNo citizens registered.\n";
			return;
		}
		HashTable occupationCount;

		for (int i = 0; i < citizenCount; i++) {
			string occ = citizens[i]->Occupation;
			string countStr = occupationCount.search(occ);

			int count = 0;
			if (countStr == "")
			{
				count = 0;
			}
			else {
				stoi(countStr);
			}

			count++;
			occupationCount.insert(occ, to_string(count));
		}

		cout << "Occupation breakdown:\n";
		for (int i = 0; i < citizenCount; i++) {
			string occ = citizens[i]->Occupation;
			string countStr = occupationCount.search(occ);
			if (countStr != "") {
				cout << "  " << occ << ": " << countStr << "\n";
				occupationCount.insert(occ, ""); 
			}
		}
	}

	void generateGenderRatio() {
		if (citizenCount == 0) {
			cout << "No citizens registered.\n";
			return;
		}

		int male = 0, female = 0;

		for (int i = 0; i < citizenCount; i++) {
			if (citizens[i]->gender == "M") { male++; }
			else if (citizens[i]->gender == "F") { female++; }
		}

		cout << "Gender Ratio Report ===\n";
		cout << "Male: " << male << " (" << (male * 100 / citizenCount) << "%)\n";
		cout << "Female: " << female << " (" << (female * 100 / citizenCount) << "%)\n";
		cout << "Ratio (M:F) = " << male << ":" << female << "\n";
	}

	void listAllCitizens() {
		if (citizenCount == 0) {
			cout << "\nNo citizens registered.\n";
			return;
		}

		cout << "\n=== Registered Citizens ===\n";
		for (int i = 0; i < citizenCount; i++) {
			cout << (i + 1) << ". " << citizens[i]->name
				<< " (Age: " << citizens[i]->age
				<< ", " << citizens[i]->Occupation << ")\n";
		}
	}
};
#endif