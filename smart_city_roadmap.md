# Smart City System - Development Roadmap Checklist

## Iteration 1: Tracer Bullet - Core Architecture

**Goal:** Build vertical slices through the entire system to validate architecture and core data structure implementations.

---

### Foundation Data Structures

- [x] Implement Singly Linked List
- [x] Implement Hash Table with Separate Chaining
- [x] Implement Stack (adapter)
- [ ] Implement N-ary Tree
- [ ] Implement Binary Max-Heap
- [ ] Implement Graph with Adjacency List
- [ ] Implement Dijkstra's Algorithm

---

### Core Use Cases (Priority Order)

#### **UC-H6: Search Citizen by CNIC** (CRITICAL)
- [x] Create Person model
- [x] Create CNICHash functor
- [x] Create IPersonRepository interface
- [x] Create CCsvPersonRepository
- [x] Create PopulationService
- [x] Create Presentation layer (main.cpp)
- [x] Test with sample data

---

#### **UC-T9: Display Complete Bus Route** (HIGH)
- [ ] Create Bus model with LinkedList<string> route
- [ ] Create IBusRepository interface
- [ ] Create CCsvBusRepository
- [ ] Create TransportService::GetBusRoute()
- [ ] Create Presentation layer menu
- [ ] Test with sample data

**DS Used:** Singly Linked List  
**Complexity:** O(n) traversal

---

#### **UC-T10: View Route History** (MEDIUM)
- [ ] Add Stack<string> to Bus model
- [ ] Add Bus::MoveTo() method
- [ ] Create TransportService::UpdateBusLocation()
- [ ] Create TransportService::GetBusRouteHistory()
- [ ] Create Presentation layer menu
- [ ] Test history tracking

**DS Used:** Stack  
**Complexity:** O(1) push/pop, O(n) display

---

#### **UC-H1, UC-H2, UC-H3: Build Sector Hierarchy** (HIGH)
- [ ] Implement N-ary Tree data structure
- [ ] Create Sector/Street/House model
- [ ] Create HousingService
- [ ] Add AddSector() method
- [ ] Add AddStreet() method
- [ ] Add AddHouse() method
- [ ] Create Presentation layer menu
- [ ] Test hierarchy creation

**DS Used:** N-ary Tree  
**Complexity:** O(n) insertion, O(n) traversal

---

#### **UC-E11: Display School Hierarchy** (HIGH)
- [ ] Create School/Department/Class model (3-level tree)
- [ ] Create EducationService
- [ ] Add RegisterSchool() method
- [ ] Add RegisterDepartment() method
- [ ] Add RegisterClass() method
- [ ] Add DisplayHierarchy() method
- [ ] Create Presentation layer menu
- [ ] Test with sample schools

**DS Used:** N-ary Tree (3-level)  
**Complexity:** O(n) traversal

---

#### **UC-M5: Find Hospital with Most Emergency Beds** (HIGH)
- [ ] Implement Binary Max-Heap
- [ ] Create Hospital model
- [ ] Create MedicalService
- [ ] Add RegisterHospital() method
- [ ] Add UpdateBedAvailability() method (reheapify)
- [ ] Add GetHospitalWithMostBeds() method
- [ ] Create Presentation layer menu
- [ ] Test heap operations

**DS Used:** Binary Max-Heap  
**Complexity:** O(log n) insert/update, O(1) extract-max

---

#### **UC-T6: Find Shortest Path Between Bus Stops** (CRITICAL)
- [ ] Implement Graph (adjacency list)
- [ ] Implement Dijkstra's Algorithm
- [ ] Create Stop model with coordinates
- [ ] Create GraphService for stops
- [ ] Add AddStop() method
- [ ] Add ConnectStops() method (weighted edges)
- [ ] Add FindShortestPath() method
- [ ] Create Presentation layer menu
- [ ] Test with sample stops

**DS Used:** Graph + Dijkstra  
**Complexity:** O((V + E) log V) with priority queue

---

#### **UC-X1: Find Nearest Bus Stop to Hospital** (CRITICAL)
- [ ] Integrate TransportService + MedicalService
- [ ] Add Hospital coordinates to model
- [ ] Add GetNearestStop() method (cross-module)
- [ ] Calculate Euclidean distance
- [ ] Create Presentation layer menu
- [ ] Test cross-module communication

**DS Used:** Graph + Hash Table  
**Complexity:** O(V) for nearest neighbor

---

### Phase 3: Integration & Testing

- [ ] Test all 8 core use cases end-to-end
- [ ] Verify data structure implementations
- [ ] Validate layered architecture
- [ ] Document complexity analysis
- [ ] Refactor based on findings

---

## Iteration 2: Feature Completion (After Tracer Bullet)

### Remaining Transport Use Cases
- [ ] UC-T1: Register Transport Company
- [ ] UC-T2: Register Bus with Route
- [ ] UC-T3: Add Bus Stop
- [ ] UC-T4: Connect Bus Stops
- [ ] UC-T5: Update Bus Location
- [ ] UC-T7: Search Bus by Number
- [ ] UC-T8: Find Nearest Bus to Location

### Remaining Education Use Cases
- [ ] UC-E1 through UC-E10

### Remaining Medical Use Cases
- [ ] UC-M1 through UC-M12

### Remaining Commercial Use Cases
- [ ] UC-C1 through UC-C6

### Remaining Public Facilities Use Cases
- [ ] UC-P1 through UC-P4

### Remaining Population & Housing Use Cases
- [ ] UC-H4, UC-H5, UC-H7-H12

### Cross-Module Use Cases
- [ ] UC-X2 through UC-X6

### System Administration
- [ ] UC-A1 through UC-A5

---

## Progress Tracking

### Iteration 1 Checklist
- [x] **1/8** UC-H6: Search Citizen by CNIC
- [ ] **0/8** UC-T9: Display Complete Bus Route
- [ ] **0/8** UC-T10: View Route History
- [ ] **0/8** UC-H1-H3: Build Sector Hierarchy
- [ ] **0/8** UC-E11: Display School Hierarchy
- [ ] **0/8** UC-M5: Find Hospital with Most Beds
- [ ] **0/8** UC-T6: Find Shortest Path
- [ ] **0/8** UC-X1: Nearest Bus Stop to Hospital

**Iteration 1 Progress:** 1/8 core use cases (12.5%)

---

## Notes

- Focus on **one use case at a time** completely (vertical slice)
- Each use case should flow: Presentation → Service → Model → Data Structure
- Test immediately after completing each use case
- Document complexity analysis as you go
- Commit to Git after each completed use case