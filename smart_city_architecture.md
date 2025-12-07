# Smart City System - Architectural Guidelines

## Overview

We follow a strict layered architecture with four core layers: Presentation, Infrastructure, Domain, and Foundation.

## Core Layers

### 1. Presentation Layer

* **Role:** Application entry point and User Interface (CLI) logic.
* **Responsibilities:** Handles menus, prompts, accepts user input (`cin`), calls the appropriate Services, and displays results (`cout`).

### 2. Persistence Layer

* **Role:** Handles the persistence logic (files).
* **Responsibilities:** Implements the Domain's Repository Interfaces (e.g., `CsvBusRepository`). Handles file I/O (`fstream`), parses CSVs, and hydrates Model objects.

### 3. Domain Layer

This layer encapsulates the core logic and data of the system. 

Services and Model sub-layers are logical divisions and not represented in the directory structure.

#### Services

* **Role:** Encapsulates business logic and orchestration.
* **Responsibilities:** Coordinating operations (e.g., calculating routes), interacting with the Model, and returning raw data to Presentation without performing I/O.

#### Model

* **Role:** Represents specific data entities.
* **Responsibilities:** Defines classes (e.g., `Bus`, `Citizen`, `Hospital`) and uses Foundation structures to store internal data.

### 4. Foundation Layer

* **Role:** Bedrock of the system containing generic, reusable code.
* **Responsibilities:** Pure implementations of Data Structures (LinkedList, Graph, etc.) and Generic Algorithms (Sorting) with zero domain knowledge.