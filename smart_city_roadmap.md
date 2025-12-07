# Smart City System - Development Roadmap

## Iteration 1: Tracer Bullet - Core Architecture

### Objective
Build vertical slices through the entire system to validate architecture and core data structure implementations.

### Core Use Cases

#### Checklist

- [x] **UC-H6:** Search Citizen by CNIC (Hash Table)
- [x] **UC-T9:** Display Complete Bus Route (Linked List)
- [x] **UC-T10:** View Route History (Stack)
- [x] **UC-H1, UC-H2, UC-H3:** Build Sector Hierarchy (N-ary Tree)
- [ ] **UC-E11:** Display School Hierarchy (N-ary Tree)
- [ ] **UC-M5:** Find Hospital with Most Emergency Beds (Binary Max-Heap)
- [ ] **UC-T6:** Find Shortest Path Between Bus Stops (Graph + Dijkstra)
- [ ] **UC-X1:** Find Nearest Bus Stop to Hospital (Graph + Hash Table)

#### 1. UC-T9: Display Complete Bus Route
**Module:** Transport  
**Data Structure:** Singly Linked List  
**Priority:** HIGH - Foundation for chaining and sequential data

#### 2. UC-H6: Search Citizen by CNIC
**Module:** Population & Housing  
**Data Structure:** Hash Table (with separate chaining)  
**Priority:** CRITICAL - Lookup pattern used across all modules

#### 3. UC-T10: View Route History
**Module:** Transport  
**Data Structure:** Stack  
**Priority:** MEDIUM - Validates LIFO operations

#### 4. UC-H1, UC-H2, UC-H3: Build Sector Hierarchy
**Module:** Population & Housing  
**Data Structure:** N-ary Tree  
**Priority:** HIGH - Multi-level hierarchical structure

#### 5. UC-E11: Display School Hierarchy
**Module:** Education  
**Data Structure:** N-ary Tree (3-level: School → Department → Class)  
**Priority:** HIGH - Organizational tree pattern

#### 6. UC-M5: Find Hospital with Most Emergency Beds
**Module:** Medical  
**Data Structure:** Binary Max-Heap  
**Priority:** HIGH - Priority queue operations

#### 7. UC-T6: Find Shortest Path Between Bus Stops
**Module:** Transport  
**Data Structure:** Graph (adjacency list) + Dijkstra's Algorithm  
**Priority:** CRITICAL - Foundation for all location-based queries

#### 8. UC-X1: Find Nearest Bus Stop to Hospital
**Modules:** Transport + Medical  
**Data Structure:** Graph + Hash Table integration  
**Priority:** CRITICAL - Validates cross-module communication