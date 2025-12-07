#pragma once
#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "../DS_Project/Graph.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/LinkedList.h"
#include "../DS_Project/Stack.h"


#include <iostream>
using namespace std;

class Bus {
private:
public:
	string BusNumber;
	string CompanyName;
	string currentStop;
	LinkedList route;
	Stack routeHistory;

	Bus(string n, string com):BusNumber(n), CompanyName(com), currentStop("Depot") {}
	void AddStop(string stopName) {
		route.insert(stopName);
	}
	void visitStop(string stopName) {
		routeHistory.push(currentStop);
		currentStop = stopName;
	}

	void displayRoute() {
		cout << " Bus: --- " << BusNumber << " (" << CompanyName << ") ---\n";
		cout << "Route: ";
		route.display();
		cout << "Current Location: " << currentStop << "\n";
	}

	void displayHistory() {
		cout << " --- Route History for: " << BusNumber << " ---\n";
		routeHistory.display();
	}
};

class TransportModule
{
private:
	Graph CityNetwork;
	HashTable BusRegistory;
	Bus* buses[100];
	int busCount;

	Bus* findBus(string busNumber) {
		for (int i = 0; i < busCount; i++) {
			if (buses[i]->BusNumber == busNumber) {
				return buses[i];
			}
		}
		return nullptr;
	}
public:
	TransportModule() : busCount(0){
		for (int i = 0; i < 100; i++)
		{
			buses[i] = nullptr;
		}
	}
	~TransportModule() {
		for (int i = 0; i < busCount; i++)
		{
			delete buses[i];
		}
	}
	// bus stops
	void addBusStop(string stopName) {
		CityNetwork.addVertex(stopName);
	}

	void connectStops(string stop1, string stop2, int distance) {
		CityNetwork.addEdge(stop1, stop2, distance);
	}
	void displayNetwork() {
		CityNetwork.display();
	}

	void registerBus(string busNumber, string companyName) {
		if (BusRegistory.search(busNumber) != "") {
			cout << "Bus: " << busNumber << " already regstred.\n";
			return;
		}

		if (busCount >= 100) {
			cout << "Bus Limit Max\n";
			return;
		}
		Bus* NewBus = new Bus(busNumber, companyName);
		buses[busCount++] = NewBus;
		BusRegistory.insert(busNumber, companyName);

		cout << "Bus: " << busNumber << " (" << companyName << ") added\n";
	}

	void addStopToBus(string busNumber, string stopName) {
		Bus* bus = findBus(busNumber);
		if (bus != nullptr) {
			bus->AddStop(stopName);
			cout << "Added " << stopName << " Stop to bus: " << busNumber << "\n";
		}
		else {
			cout << "Bus: " << busNumber << "not found\n";
		}
	}

	void displayBusRoute(string busNumber) {
		Bus* bus = findBus(busNumber);
		if (bus != nullptr) {
			bus->displayRoute();
		}
		else {
			cout << "Bus: " << busNumber << " not found\n";
		}
	}

	void moveBus(string busNumber, string stopName) {
		Bus* bus = findBus(busNumber);
		if (bus != nullptr) {
			bus->visitStop(stopName);
			cout << "Bus " << busNumber << " moved to: " << stopName << "\n";
		}
		else {
			cout << "Bus: " << busNumber << " not found!\n";
		}
	}

	void showBusHistory(string busNumber) {
		Bus* bus = findBus(busNumber);
		if (bus != nullptr) {
			bus->displayHistory();
		}
		else {
			cout << "Bus: " << busNumber << " not found!\n";
		}
	}

	void findShortestPath(string Source, string Destination) {
		CityNetwork.FindShortestPath(Source, Destination);
	}

	void searchBus(string busNumber) {
		string company = BusRegistory.search(busNumber);
		if (company != "") {
			cout << "Bus Found\nData: ";
			cout << "Bus Number: " << busNumber << " Company: " << company << "\n";

			Bus* bus = findBus(busNumber);
			if (bus != nullptr)
			{
				cout << "Current Location: " << bus->currentStop << endl;
			}
		}
		else {
			cout << "Bus: " << busNumber << " not found!\n";
		}
	}

	void listAllBuses() {
		if (busCount == 0) {
			cout << "No buses registered\n";
			return;
		}

		cout << "Registred Buses:\n";
		for (int i = 0; i < busCount; i++)
		{
			cout << (i + 1) << ". Bus " << buses[i]->BusNumber << "(" << buses[i]->CompanyName << ") is at " << buses[i]->currentStop << endl;
		}
	}
};

#endif // !TRANSPORT_H
