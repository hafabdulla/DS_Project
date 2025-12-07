#pragma once
#ifndef MEDICAL_H
#define MEDICAL_H

#include "../DS_Project/PriorityQueue.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/Graph.h"
#include <iostream>
using namespace std;

class Doctor {
public:
	string name;
	string specialization;
	string hospitalName;

	Doctor(string n, string spec, string hospital) :name(n), specialization(spec), hospitalName(hospital){}
	string toString() {
		return name + " | " + specialization + " | " + hospitalName;
	}
};

class Hospital {
public:
	string name;
	string sector;
	int emergencyBeds;
	string specializations;
	Hospital(string n, string s, int beds, string spec) :name(n), sector(s), emergencyBeds(beds), specializations(spec){}

};

class Medicine {
public:
	string name;
	string formula;
	int price;
	string pharmacyName;

	Medicine(string n, string f, int p, string pharmacy):name(n), formula(f), price(p), pharmacyName(pharmacy){}

	string toString() {
		return name + "|" + formula + "|" + to_string(price) + "|" + pharmacyName;
	}
};

class MedicalModule {
private:
	PriorityQueue emergencyQueue;       //priority queue for emergency beds
	HashTable hospitalRegistry;
	HashTable doctorBySpecialization;   // doctors grouped by specialization
	HashTable medicineByName;
	HashTable medicineByFormula;
	Graph medicalNetwork;

	Hospital* hospitals[100];
	int hospitalCount;

	Doctor* doctors[500];
	int doctorCount;

	Medicine* medicines[500];
	int medicineCount;

	void parseMedicineData(string data) {
		//format: name|formula|price|pharmacy
		string tokens[4];
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
			cout << "Formula: " << tokens[1] << "\n";
			cout << "Price: Rs." << tokens[2] << "\n";
			cout << "Pharmacy: " << tokens[3] << "\n";
		}
	}

public:
	MedicalModule() : hospitalCount(0), doctorCount(0), medicineCount(0) {
		for (int i = 0; i < 100; i++) hospitals[i] = nullptr;
		for (int i = 0; i < 500; i++) doctors[i] = nullptr;
		for (int i = 0; i < 500; i++) medicines[i] = nullptr;
	}

	~MedicalModule() {
		for (int i = 0; i < hospitalCount; i++) delete hospitals[i];
		for (int i = 0; i < doctorCount; i++) delete doctors[i];
		for (int i = 0; i < medicineCount; i++) delete medicines[i];
	}

	void registerHospital(string name, string sector, int emergencyBeds, string specializations) {
		if (hospitalCount >= 100) {
			cout << "Hospital limit reached. No Space.\n";
			return;
		}

		Hospital* newHospital = new Hospital(name, sector, emergencyBeds, specializations);
		hospitals[hospitalCount++] = newHospital;
		hospitalRegistry.insert(name, sector + "|" + to_string(emergencyBeds) + "|" + specializations);
		emergencyQueue.insert(name, emergencyBeds);
		medicalNetwork.addVertex(name);
		cout << "Registered: " << name << " (" << sector << ", " << emergencyBeds << " beds)\n";
	}

	void registerDoctor(string name, string specialization, string hospitalName) {
		if (doctorCount >= 500) {
			cout << "Doctor limit reached\n";
			return;
		}

		Doctor* newDoctor = new Doctor(name, specialization, hospitalName);
		doctors[doctorCount++] = newDoctor;

		// Add to specialization hash (for search)
		string existing = doctorBySpecialization.search(specialization);
		if (existing == "") {
			doctorBySpecialization.insert(specialization, name + "@" + hospitalName);
		}
		else {
			doctorBySpecialization.insert(specialization, existing + ";" + name + "@" + hospitalName);
		}

		cout << "Registered Dr. " << name << " (" << specialization << ") at " << hospitalName << "\n";
	}

	void findBestEmergencyHospital() {
		if (emergencyQueue.isEmpty()) {
			cout << "No Hospitals registred\n";
			return;
		}
		HeapNode best = emergencyQueue.peek();
		cout << "Best Hoospital:\n";
		cout << best.Name << " available beds: " << best.priority << "\n";
	}

	void updateEmergencyBeds(string hospitalName, int newBedCount) {

		HeapNode current = emergencyQueue.extractMax();

		// Find and update the hospital
		bool found = false;
		if (current.Name == hospitalName) {
			emergencyQueue.insert(hospitalName, newBedCount);
			found = true;
			cout << "Updated: " << hospitalName << " now has " << newBedCount << " beds\n";
		}
		else {
			emergencyQueue.insert(current.Name, current.priority);
		}

		if (!found) {
			cout << "If hospital not at top it remains unchanged in queue\n";
		}
	}

	void searchDoctorBySpecialization(string specialization) {
		string result = doctorBySpecialization.search(specialization);

		if (result == "") {
			cout << "No doctors found with specialization: " << specialization << "\n";
			return;
		}

		cout << "\nDoctors with " << specialization << " specialization\n";

		string current = "";
		int count = 1;
		for (int i = 0; i < result.length(); i++)
		{
			if (result[i] == ';') {
				int atPos = current.find('@');
				if (atPos != string::npos) {
					string docName = current.substr(0, atPos);
					string hospital = current.substr(atPos + 1);
					cout << count++ << ". Dr. " << docName << " at " << hospital << "\n";
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
				string docName = current.substr(0, atPos);
				string hospital = current.substr(atPos + 1);
				cout << count << ". Dr. " << docName << " at " << hospital << "\n";
			}
		}
	}

	void addMedicine(string name, string formula, int price, string pharmacyName) {
		if (medicineCount >= 500) {
			cout << "Medicine limit reached!\n";
			return;
		}

		Medicine* newMedicine = new Medicine(name, formula, price, pharmacyName);
		medicines[medicineCount++] = newMedicine;

		medicineByName.insert(name, newMedicine->toString());
		medicineByFormula.insert(formula, newMedicine->toString());

		cout << "Added: " << name << " (" << formula << ") - Rs." << price << " at " << pharmacyName << "\n";
	}

	void searchMedicineByName(string name) {
		string result = medicineByName.search(name);

		if (result == "") {
			cout << "Medicine '" << name << "' not found!\n";
			return;
		}

		cout << "Medicine Found:\n";
		parseMedicineData(result);
	}
	void searchMedicineByFormula(string formula) {
		string result = medicineByFormula.search(formula);

		if (result == "") {
			cout << "No medicine found with formula: " << formula << "\n";
			return;
		}

		cout << "Medicine Found by Formula\n";
		parseMedicineData(result);
	}

	void connectHospitals(string hospital1, string hospital2, int distance) {
		medicalNetwork.addEdge(hospital1, hospital2, distance);
	}

	void findNearestHospital(string source, string destination) {
		medicalNetwork.FindShortestPath(source, destination);
	}
	void displayEmergencyQueue() {
		cout << "Emergency Bed Availability:\n";
		emergencyQueue.display();
	}

	void listAllHospitals() {
		if (hospitalCount == 0) {
			cout << "No hospitals registered.\n";
			return;
		}

		cout << "Registered Hospitals\n";
		for (int i = 0; i < hospitalCount; i++) {
			cout << (i + 1) << ". " << hospitals[i]->name << " (" << hospitals[i]->sector << ") - " << hospitals[i]->emergencyBeds << " beds\n";
		}
	}
	void listAllDoctors() {
		if (doctorCount == 0) {
			cout << "No doctors registered.\n";
			return;
		}

		cout << "\n=== Registered Doctors ===\n";
		for (int i = 0; i < doctorCount; i++) {
			cout << (i + 1) << ". Dr. " << doctors[i]->name << " (" << doctors[i]->specialization << ") at " << doctors[i]->hospitalName << "\n";
		}
	}
};
#endif