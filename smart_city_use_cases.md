# Smart City Management System - Use Cases

## Table of Contents
1. [Transport Sector](#1-transport-sector)
2. [Education Sector](#2-education-sector)
3. [Medical Sector](#3-medical-sector)
4. [Commercial Sector](#4-commercial-sector)
5. [Public Facilities Sector](#5-public-facilities-sector)
6. [Population & Housing Sector](#6-population--housing-sector)
7. [Cross-Module Use Cases](#7-cross-module-use-cases)
8. [Bonus/Optional Use Cases](#8-bonusoptional-use-cases)
9. [System Administration Use Cases](#9-system-administration-use-cases)

---

## 1. Transport Sector

### UC-T1: Register Transport Company
**Actor:** System Administrator  
**Description:** Add a new transport company to the system  
**Preconditions:** None  
**Postconditions:** Company is registered and can add buses  

### UC-T2: Register Bus with Route
**Actor:** Transport Manager  
**Description:** Add a new bus with its route information  
**Preconditions:** Transport company exists, bus stops exist  
**Postconditions:** Bus is added to hash table, route stored as linked list  

### UC-T3: Add Bus Stop
**Actor:** Transport Manager  
**Description:** Register a new bus stop with location coordinates  
**Preconditions:** Valid coordinates provided  
**Postconditions:** Stop added as graph node  

### UC-T4: Connect Bus Stops
**Actor:** Transport Manager  
**Description:** Create a connection between two stops with distance  
**Preconditions:** Both stops exist  
**Postconditions:** Weighted edge added to graph  

### UC-T5: Update Bus Location
**Actor:** System (Real-time tracking)  
**Description:** Update current stop of a bus  
**Preconditions:** Bus exists  
**Postconditions:** Bus current location updated  

### UC-T6: Find Shortest Path Between Stops
**Actor:** Passenger/Planner  
**Description:** Calculate shortest route between two bus stops  
**Preconditions:** Both stops exist and are connected  
**Postconditions:** Shortest path displayed with distance  
**Algorithm:** Dijkstra's Algorithm  

### UC-T7: Search Bus by Number
**Actor:** Passenger  
**Description:** Get complete details of a bus by its number  
**Preconditions:** Bus number provided  
**Postconditions:** Bus details displayed (route, current location, company)  
**DS Used:** Hash Table lookup - O(1) average  

### UC-T8: Find Nearest Bus to Location
**Actor:** Passenger  
**Description:** Find closest bus to user's current coordinates  
**Preconditions:** Valid coordinates provided  
**Postconditions:** Nearest bus and distance displayed  

### UC-T9: Display Complete Bus Route
**Actor:** Passenger  
**Description:** Show all stops in a bus's route in sequence  
**Preconditions:** Bus exists  
**Postconditions:** Ordered list of stops displayed  
**DS Used:** Linked List traversal  

### UC-T10: View Route History
**Actor:** System/Administrator  
**Description:** Display travel history of a bus (last N stops visited)  
**Preconditions:** Bus has traveled  
**Postconditions:** Route history shown in reverse order  
**DS Used:** Stack  

---

## 2. Education Sector

### UC-E1: Register School
**Actor:** Education Administrator  
**Description:** Add a new school to the system  
**Preconditions:** Valid school details provided  
**Postconditions:** School added to hash table and tree structure  

### UC-E2: Add Campus/Branch
**Actor:** School Administrator  
**Description:** Add a branch/campus under a school  
**Preconditions:** Parent school exists  
**Postconditions:** Campus added as child in N-ary tree  

### UC-E3: Register Department
**Actor:** School Administrator  
**Description:** Add a department to a school  
**Preconditions:** School exists  
**Postconditions:** Department node added in tree (Level 2)  

### UC-E4: Register Class
**Actor:** School Administrator  
**Description:** Add a class under a department  
**Preconditions:** Department exists  
**Postconditions:** Class node added in tree (Level 3)  

### UC-E5: Register Student
**Actor:** School Administrator  
**Description:** Enroll a student in a specific class  
**Preconditions:** Class exists  
**Postconditions:** Student added to class node  

### UC-E6: Register Faculty Member
**Actor:** School Administrator  
**Description:** Add a teacher/faculty to a department  
**Preconditions:** Department exists  
**Postconditions:** Faculty record created  

### UC-E7: Search Schools by Subject
**Actor:** Parent/Student  
**Description:** Find all schools offering a specific subject  
**Preconditions:** Subject name provided  
**Postconditions:** List of matching schools displayed  

### UC-E8: Search School by ID
**Actor:** User  
**Description:** Quickly retrieve school details using ID  
**Preconditions:** School ID provided  
**Postconditions:** School information displayed  
**DS Used:** Hash Table - O(1)  

### UC-E9: Find Nearest School to Location
**Actor:** Parent/Student  
**Description:** Find closest school from given coordinates  
**Preconditions:** Valid coordinates  
**Postconditions:** Nearest school with distance shown  

### UC-E10: Rank Schools by Rating
**Actor:** Parent/Education Planner  
**Description:** Display schools in order of rating  
**Preconditions:** Schools have ratings  
**Postconditions:** Sorted list displayed (highest first)  
**DS Used:** Priority Queue (Min-Heap)  

### UC-E11: Display School Hierarchy
**Actor:** Administrator  
**Description:** Show complete organizational structure of a school  
**Preconditions:** School exists  
**Postconditions:** Tree structure displayed (School→Dept→Class→Students)  
**DS Used:** Tree traversal  

---

## 3. Medical Sector

### UC-M1: Register Hospital
**Actor:** Health Administrator  
**Description:** Add a new hospital with location and specializations  
**Preconditions:** Valid hospital details  
**Postconditions:** Hospital added to hash table and graph  

### UC-M2: Register Doctor
**Actor:** Hospital Administrator  
**Description:** Add a doctor with specialization  
**Preconditions:** Hospital exists  
**Postconditions:** Doctor registered and indexed by specialization  

### UC-M3: Register Patient
**Actor:** Hospital Staff  
**Description:** Add patient record to hospital system  
**Preconditions:** Valid patient details  
**Postconditions:** Patient record created with unique ID  

### UC-M4: Update Emergency Bed Availability
**Actor:** Hospital Staff  
**Description:** Update number of available emergency beds  
**Preconditions:** Hospital exists  
**Postconditions:** Bed count updated in max-heap  
**DS Used:** Binary Max-Heap (reheapify)  

### UC-M5: Find Hospital with Most Emergency Beds
**Actor:** Emergency Services/Ambulance  
**Description:** Get hospital with maximum available emergency beds  
**Preconditions:** Hospitals exist  
**Postconditions:** Hospital with most beds returned  
**DS Used:** Max-Heap extract-max - O(log n)  

### UC-M6: Find Nearest Hospital
**Actor:** Patient/Emergency Services  
**Description:** Locate closest hospital from coordinates  
**Preconditions:** Valid location  
**Postconditions:** Nearest hospital with distance displayed  

### UC-M7: Search Doctor by Specialization
**Actor:** Patient  
**Description:** Find all doctors with specific specialization  
**Preconditions:** Specialization name provided  
**Postconditions:** List of matching doctors shown  
**DS Used:** Hash Table with specialization index  

### UC-M8: Register Pharmacy
**Actor:** Health Administrator  
**Description:** Add pharmacy to the system  
**Preconditions:** Valid pharmacy details  
**Postconditions:** Pharmacy registered  

### UC-M9: Add Medicine to Pharmacy
**Actor:** Pharmacist  
**Description:** Register medicine with name, formula, and price  
**Preconditions:** Pharmacy exists  
**Postconditions:** Medicine added to hash table  
**DS Used:** Separate hash tables for name and formula  

### UC-M10: Search Medicine by Name
**Actor:** Patient/Pharmacist  
**Description:** Find medicine details using name  
**Preconditions:** Medicine name provided  
**Postconditions:** Medicine info displayed (formula, price, pharmacy)  
**DS Used:** Hash Table - O(1)  

### UC-M11: Search Medicine by Formula
**Actor:** Doctor/Pharmacist  
**Description:** Find medicines with specific chemical formula  
**Preconditions:** Formula provided  
**Postconditions:** All matching medicines shown  
**DS Used:** Hash Table with formula as key  

### UC-M12: Find Nearest Pharmacy
**Actor:** Patient  
**Description:** Locate closest pharmacy from location  
**Preconditions:** Valid coordinates  
**Postconditions:** Nearest pharmacy with distance shown  

---

## 4. Commercial Sector

### UC-C1: Register Shopping Mall
**Actor:** Commercial Administrator  
**Description:** Add a new mall to the system  
**Preconditions:** Valid mall details with location  
**Postconditions:** Mall added to hash table and graph  

### UC-C2: Add Product to Mall
**Actor:** Mall Manager  
**Description:** Register a product with category and price  
**Preconditions:** Mall exists  
**Postconditions:** Product added to hash table  

### UC-C3: Search Product by Name
**Actor:** Shopper  
**Description:** Find product details by name  
**Preconditions:** Product name provided  
**Postconditions:** Product info shown (mall, price, category)  
**DS Used:** Hash Table - O(1)  

### UC-C4: Search Products by Category
**Actor:** Shopper  
**Description:** Find all products in a specific category  
**Preconditions:** Category name provided  
**Postconditions:** List of matching products displayed  

### UC-C5: Find Nearest Mall
**Actor:** Shopper  
**Description:** Locate closest mall from coordinates  
**Preconditions:** Valid location  
**Postconditions:** Nearest mall with distance shown  

### UC-C6: Find Nearest Mall with Specific Product
**Actor:** Shopper  
**Description:** Find closest mall that has a specific product  
**Preconditions:** Product name and location provided  
**Postconditions:** Nearest mall carrying the product shown  

---

## 5. Public Facilities Sector

### UC-P1: Register Public Facility
**Actor:** Municipal Administrator  
**Description:** Add a facility (mosque, park, water cooler)  
**Preconditions:** Valid facility details with location  
**Postconditions:** Facility added as graph node  

### UC-P2: Find Nearest Facility by Type
**Actor:** Citizen  
**Description:** Locate nearest facility of specific type  
**Preconditions:** Facility type and location provided  
**Postconditions:** Nearest matching facility shown  

### UC-P3: Find All Facilities in Sector
**Actor:** Citizen/Planner  
**Description:** List all facilities within a specific sector  
**Preconditions:** Sector name provided  
**Postconditions:** All facilities in sector displayed  

### UC-P4: Connect Facility to Transport Network
**Actor:** City Planner  
**Description:** Link facility to nearest bus stops  
**Preconditions:** Facility and stops exist  
**Postconditions:** Edges created in graph  

---

## 6. Population & Housing Sector

### UC-H1: Add Sector
**Actor:** Municipal Administrator  
**Description:** Register a new sector in Islamabad  
**Preconditions:** Valid sector name  
**Postconditions:** Sector added as child of root in N-ary tree  

### UC-H2: Add Street to Sector
**Actor:** Municipal Administrator  
**Description:** Register a street under a sector  
**Preconditions:** Sector exists  
**Postconditions:** Street added as child node  

### UC-H3: Add House to Street
**Actor:** Municipal Administrator  
**Description:** Register a house with house number  
**Preconditions:** Street exists  
**Postconditions:** House added as leaf node  

### UC-H4: Register Family
**Actor:** Census Officer  
**Description:** Add a family to a house  
**Preconditions:** House exists  
**Postconditions:** Family tree structure created  

### UC-H5: Register Individual
**Actor:** Census Officer  
**Description:** Add a person to a family with CNIC  
**Preconditions:** Family exists  
**Postconditions:** Person added to family tree and CNIC hash table  

### UC-H6: Search Citizen by CNIC
**Actor:** Government Official  
**Description:** Retrieve citizen details using CNIC  
**Preconditions:** Valid CNIC provided  
**Postconditions:** Complete citizen info displayed (name, age, address, occupation)  
**DS Used:** Hash Table - O(1)  

### UC-H7: Generate Age Distribution Report
**Actor:** Census Analyst  
**Description:** Calculate population distribution across age groups  
**Preconditions:** Population data exists  
**Postconditions:** Age group statistics displayed  
**Example:** 0-18: 25%, 19-35: 40%, 36-60: 30%, 60+: 5%  

### UC-H8: Generate Occupation Summary
**Actor:** Labor Department  
**Description:** Count citizens by occupation category  
**Preconditions:** Population data exists  
**Postconditions:** Occupation breakdown shown  
**Example:** Engineers: 150, Teachers: 80, Doctors: 45, etc.  

### UC-H9: Calculate Population Density by Sector
**Actor:** Urban Planner  
**Description:** Determine population per unit area for each sector  
**Preconditions:** Sector and population data exists  
**Postconditions:** Density metrics displayed per sector  

### UC-H10: Generate Gender Ratio Report
**Actor:** Census Analyst  
**Description:** Calculate male-to-female ratio  
**Preconditions:** Population data exists  
**Postconditions:** Gender statistics displayed  

### UC-H11: Find All Residents of a Sector
**Actor:** Administrator  
**Description:** List all citizens living in a specific sector  
**Preconditions:** Sector exists  
**Postconditions:** Complete resident list shown  
**DS Used:** Tree traversal  

### UC-H12: Display Sector Hierarchy
**Actor:** Administrator  
**Description:** Show complete structure: Islamabad → Sectors → Streets → Houses  
**Preconditions:** Data exists  
**Postconditions:** Tree structure displayed  

---

## 7. Cross-Module Use Cases

### UC-X1: Find Nearest Bus Stop to Hospital
**Actor:** Patient/Visitor  
**Description:** Find closest bus stop to a specific hospital  
**Preconditions:** Hospital exists, bus stops exist  
**Postconditions:** Nearest stop with distance shown  
**Modules:** Transport + Medical  

### UC-X2: Find Nearest Hospital from Bus Stop
**Actor:** Passenger  
**Description:** Locate nearest hospital from a bus stop  
**Preconditions:** Bus stop exists  
**Postconditions:** Nearest hospital shown  
**Modules:** Transport + Medical  

### UC-X3: Route from Home to School
**Actor:** Student/Parent  
**Description:** Find transport route from residence to school  
**Preconditions:** Home address and school exist  
**Postconditions:** Complete route with transfers shown  
**Modules:** Transport + Education + Housing  

### UC-X4: Emergency Response Route
**Actor:** Emergency Services  
**Description:** Find fastest route to hospital with available beds  
**Preconditions:** Emergency location provided  
**Postconditions:** Optimal route to best hospital shown  
**Modules:** Transport + Medical  

### UC-X5: Nearest Facility of Any Type
**Actor:** Citizen  
**Description:** Find closest facility regardless of type  
**Preconditions:** Location provided  
**Postconditions:** Nearest facility shown (could be hospital, school, mall, park, etc.)  
**Modules:** All modules  

### UC-X6: Survey Specific Sector
**Actor:** Government Official  
**Description:** Get complete demographic + facility report for a sector  
**Preconditions:** Sector exists  
**Postconditions:** Comprehensive report (population, facilities, connectivity)  
**Modules:** Housing + Public Facilities + Transport  

---

## 8. Bonus/Optional Use Cases

### UC-B1: Track School Bus Real-Time
**Actor:** Parent/School  
**Description:** Monitor current location of school bus  
**Preconditions:** School bus tracking enabled  
**Postconditions:** Live location shown  

### UC-B2: Integrate Airport/Railway
**Actor:** Transport Planner  
**Description:** Add airport/railway as special graph nodes  
**Preconditions:** Transport network exists  
**Postconditions:** Inter-city connectivity established  

### UC-B3: Simulate Real-Time Route
**Actor:** System  
**Description:** Animate bus movement through route  
**Preconditions:** Bus route exists  
**Postconditions:** Visual simulation displayed  

### UC-B4: Emergency Transport Routing
**Actor:** Ambulance/Emergency  
**Description:** Calculate priority route avoiding traffic  
**Preconditions:** Emergency declared  
**Postconditions:** Fastest route with alternatives shown  

### UC-B5: Generate Population Heatmap
**Actor:** Urban Planner  
**Description:** Visualize population density across city  
**Preconditions:** Population data exists  
**Postconditions:** Density map/data shown  

---

## 9. System Administration Use Cases

### UC-A1: Load Sample Data
**Actor:** Administrator  
**Description:** Import predefined dataset (Appendix-1)  
**Preconditions:** System initialized  
**Postconditions:** All sample data loaded  

### UC-A2: Clear All Data
**Actor:** Administrator  
**Description:** Reset system to initial state  
**Preconditions:** Confirmation provided  
**Postconditions:** All data structures cleared  

### UC-A3: Display System Statistics
**Actor:** Administrator  
**Description:** Show counts and memory usage  
**Preconditions:** None  
**Postconditions:** Stats displayed (buses, stops, hospitals, citizens, etc.)  

### UC-A4: Export Data
**Actor:** Administrator  
**Description:** Save current state to file  
**Preconditions:** Data exists  
**Postconditions:** Data written to file  

### UC-A5: Import Data from File
**Actor:** Administrator  
**Description:** Load data from previously exported file  
**Preconditions:** Valid file exists  
**Postconditions:** Data loaded into system  

---

## Summary

**Total Use Cases:** 70+
- Transport Sector: 10 use cases
- Education Sector: 11 use cases
- Medical Sector: 12 use cases
- Commercial Sector: 6 use cases
- Public Facilities: 4 use cases
- Population & Housing: 12 use cases
- Cross-Module: 6 use cases
- Bonus/Optional: 5 use cases
- System Administration: 5 use cases

Each use case should be implemented with:
- Proper input validation
- Error handling
- User-friendly console output
- Efficient data structure operations
- Appropriate complexity analysis