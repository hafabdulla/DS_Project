#pragma once
#ifndef EDUCATION_H
#define EDUCATION_H

#include "../DS_Project/HashTable.h"
#include "../DS_Project/PriorityQueue.h"
#include "../DS_Project/Graph.h"
#include <iostream>
using namespace std;

// 3-Level Tree Node: School -> Department -> Class
struct ClassNode {
    string className;
    int studentCount;
    ClassNode* nextClass;

    ClassNode(string name, int count) : className(name), studentCount(count), nextClass(nullptr) {}
};

struct DepartmentNode {
    string deptName;
    ClassNode* classes;
    DepartmentNode* nextDept;

    DepartmentNode(string name) : deptName(name), classes(nullptr), nextDept(nullptr) {}

    void addClass(string className, int studentCount) {
        ClassNode* newClass = new ClassNode(className, studentCount);
        newClass->nextClass = classes;
        classes = newClass;
    }

    void displayClasses() {
        cout << "    Department: " << deptName << "\n";
        ClassNode* curr = classes;
        while (curr != nullptr) {
            cout << "      -> Class: " << curr->className << " (" << curr->studentCount << " students)\n";
            curr = curr->nextClass;
        }
    }
};

class SchoolNode {
public:
    string schoolName;
    string sector;
    float rating;
    string subjects;
    DepartmentNode* departments;

    SchoolNode(string name, string sec, float rate, string subj)
        : schoolName(name), sector(sec), rating(rate), subjects(subj), departments(nullptr) {
    }

    void addDepartment(string deptName) {
        DepartmentNode* newDept = new DepartmentNode(deptName);
        newDept->nextDept = departments;
        departments = newDept;
        cout << "Added department: " << deptName << " to " << schoolName << "\n";
    }

    DepartmentNode* findDepartment(string deptName) {
        DepartmentNode* curr = departments;
        while (curr != nullptr) {
            if (curr->deptName == deptName) return curr;
            curr = curr->nextDept;
        }
        return nullptr;
    }

    void displayHierarchy() {
        cout << "\n=== School: " << schoolName << " (" << sector << ") ===\n";
        cout << "Rating: " << rating << " | Subjects: " << subjects << "\n";

        DepartmentNode* dept = departments;
        while (dept != nullptr) {
            dept->displayClasses();
            dept = dept->nextDept;
        }
    }
};

class EducationModule {
private:
    SchoolNode* schools[50];
    int schoolCount;

    HashTable schoolRegistry;
    HashTable subjectIndex;
    PriorityQueue schoolRankings;
    Graph schoolNetwork;

public:
    EducationModule() : schoolCount(0) {
        for (int i = 0; i < 50; i++) schools[i] = nullptr;
    }

    ~EducationModule() {
        for (int i = 0; i < schoolCount; i++) {
            if (schools[i] != nullptr) {
                // Clean up departments and classes
                DepartmentNode* dept = schools[i]->departments;
                while (dept != nullptr) {
                    ClassNode* cls = dept->classes;
                    while (cls != nullptr) {
                        ClassNode* temp = cls;
                        cls = cls->nextClass;
                        delete temp;
                    }
                    DepartmentNode* tempDept = dept;
                    dept = dept->nextDept;
                    delete tempDept;
                }
                delete schools[i];
            }
        }
    }

    void registerSchool(string schoolID, string name, string sector, float rating, string subjects) {
        if (schoolCount >= 50) {
            cout << "School limit reached!\n";
            return;
        }

        SchoolNode* newSchool = new SchoolNode(name, sector, rating, subjects);
        schools[schoolCount++] = newSchool;

        // Hash registration
        schoolRegistry.insert(schoolID, name + "|" + sector + "|" + to_string(rating));

        // Subject indexing
        string subjectList = subjects;
        string currentSubject = "";
        for (int i = 0; i <= subjectList.length(); i++) {
            if (i == subjectList.length() || subjectList[i] == ',') {
                if (currentSubject != "") {
                    // Trim spaces
                    while (currentSubject[0] == ' ') {
                        currentSubject = currentSubject.substr(1);
                    }
                    string existing = subjectIndex.search(currentSubject);
                    if (existing == "") {
                        subjectIndex.insert(currentSubject, name);
                    }
                    else {
                        subjectIndex.insert(currentSubject, existing + ";" + name);
                    }
                    currentSubject = "";
                }
            }
            else {
                currentSubject += subjectList[i];
            }
        }

        //inserting to priority
        int priority = (int)(rating * 10);
        schoolRankings.insert(name, priority);

        // inserting to graph
        schoolNetwork.addVertex(name);

        cout << "Registered school: " << name << " (Rating: " << rating << ")\n";
    }

    void addDepartment(string schoolName, string deptName) {
        SchoolNode* school = findSchool(schoolName);
        if (school != nullptr) {
            school->addDepartment(deptName);
        }
        else {
            cout << "School '" << schoolName << "' not found!\n";
        }
    }

    void addClass(string schoolName, string deptName, string className, int studentCount) {
        SchoolNode* school = findSchool(schoolName);
        if (school != nullptr) {
            DepartmentNode* dept = school->findDepartment(deptName);
            if (dept != nullptr) {
                dept->addClass(className, studentCount);
                cout << "Added class: " << className << " to " << deptName << " (" << schoolName << ")\n";
            }
            else {
                cout << "Department '" << deptName << "' not found!\n";
            }
        }
        else {
            cout << "School '" << schoolName << "' not found!\n";
        }
    }

    void displaySchoolHierarchy(string schoolName) {
        SchoolNode* school = findSchool(schoolName);
        if (school != nullptr) {
            school->displayHierarchy();
        }
        else {
            cout << "School '" << schoolName << "' not found!\n";
        }
    }

    void searchSchoolsBySubject(string subject) {
        string result = subjectIndex.search(subject);

        if (result == "") {
            cout << "No schools found offering: " << subject << "\n";
            return;
        }

        cout << "Schools offering " << subject << endl;

        string current = "";
        int count = 1;
        for (int i = 0; i <= result.length(); i++) {
            if (i == result.length() || result[i] == ';') {
                if (current != "") {
                    cout << count++ << ". " << current << "\n";
                    current = "";
                }
            }
            else {
                current += result[i];
            }
        }
    }

    void displayTopRankedSchools() {
        cout << "Top Ranked Schools (Priority Queue):\n";
        schoolRankings.display();
    }

    void connectSchools(string school1, string school2, int distance) {
        schoolNetwork.addEdge(school1, school2, distance);
    }

    void findNearestSchool(string fromLocation, string toSchool) {
        schoolNetwork.FindShortestPath(fromLocation, toSchool);
    }

    void listAllSchools() {
        if (schoolCount == 0) {
            cout << "No schools registered.\n";
            return;
        }

        cout << "Registered Schools:\n";
        for (int i = 0; i < schoolCount; i++) {
            cout << (i + 1) << ". " << schools[i]->schoolName
                << " (" << schools[i]->sector << ") - Rating: "
                << schools[i]->rating << "\n";
        }
    }

private:
    SchoolNode* findSchool(string schoolName) {
        for (int i = 0; i < schoolCount; i++) {
            if (schools[i]->schoolName == schoolName) {
                return schools[i];
            }
        }
        return nullptr;
    }
};

#endif // EDUCATION_H