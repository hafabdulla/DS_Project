# Smart City System - Architectural Guidelines

## Overview

We follow a strict layered architecture with three core layers: Presentation, Domain, and Foundation.

## Core Layers

### 1. Presentation Layer

* **Role:** Application entry point and User Interface (CLI) logic.
* **Responsibilities:** Handles menus, prompts, accepts user input (`cin`), calls the appropriate Services, and displays results (`cout`).

### 2. Domain Layer

This layer encapsulates the core logic and data of the system. Note that each module folder (e.g.,  `Transport`, `Medical`) represents the domain layer.

Services and Model sub-layers are logical divisions and not represented in the directory structure.

#### Services

* **Role:** Encapsulates business logic and orchestration.
* **Responsibilities:** Coordinating operations (e.g., calculating routes), interacting with the Model, and returning raw data to Presentation without performing I/O.

#### Model

* **Role:** Represents specific data entities.
* **Responsibilities:** Defines classes (e.g., `Bus`, `Citizen`, `Hospital`) and uses Foundation structures to store internal data.

### 3. Foundation Layer

* **Role:** Bedrock of the system containing generic, reusable code.
* **Responsibilities:** Pure implementations of Data Structures (LinkedList, Graph, etc.) and Generic Algorithms (Sorting) with zero domain knowledge.

## Example Directory Structure

```text
SmartCity/
├── Foundation/                  <-- Shared Generic Data Structures
│   ├── LinkedList.h
│   ├── Graph.h
│   └── Stack.h
├── Transport/                   <-- Feature Module
│   ├── Bus.h                    <-- Model Entity
│   ├── Stop.h                   <-- Model Entity
│   └── TransportService.h       <-- Service Logic
├── Medical/                     <-- Feature Module
│   ├── Hospital.h               <-- Model Entity
│   ├── Patient.h                <-- Model Entity
│   └── MedicalService.h         <-- Service Logic
└── Presentation/                <-- UI / Application Entry
    ├── main.cpp
    └── Menus/
