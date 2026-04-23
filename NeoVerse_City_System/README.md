# NeoVerse: AI City Survival System

## Overview
A console-based C++ simulation system that manages a smart city's data, events, and agents using STL containers, algorithms, and object-oriented programming principles. This system demonstrates dynamic data structures, algorithm efficiency, and real-world problem solving.

## Login Credentials
- Username: `admin`, Password: `admin123` (HIGH clearance)
- Username: `operator`, Password: `op456` (MEDIUM clearance)
- Username: `viewer`, Password: `view789` (LOW clearance)

## How to Build and Run
1. Open this folder in VS Code
2. Run `make` in the terminal to build
3. Run `make run` or `./build/neoverse.exe` to execute

## Features Implemented

### 1. AI Agent Authentication & Access Control
- **Engineer Class**: ID, username, encrypted password, clearance level
- **STL Usage**: `vector<Engineer>` for storage, `std::find_if` for login search
- **Big-O Analysis**: Login search is O(n) linear search (suitable for small engineer database < 100)

### 2. City Data Management (Dynamic Containers)
- **Vector for Sensor Readings**: Fast random access O(1) for daily data
- **Linked List for Historical Logs**: Unbounded growth with O(1) insertion
- **Operations**: Add, remove, traverse, and display data

### 3. Event Processing System (Real-Time Simulation)
- **Queue (FIFO)**: `queue<Event>` for regular city events processed in arrival order
- **Stack (LIFO)**: `stack<EmergencyEvent>` for emergency overrides processed immediately
- **STL Algorithms**: Filtering and prioritization using `<algorithm>` library

### 4. Object-Oriented City Architecture
- **Base Class**: `CityZone` with virtual `processEvent()` method
- **Derived Classes**: `ResidentialZone`, `IndustrialZone`, `CommercialZone`
- **OOP Concepts**: Encapsulation, Inheritance, Polymorphism, Constructors/Destructors

### 5. STL Algorithms & Performance Optimisation
- **std::sort**: Sort events by priority (O(n log n))
- **std::find**: Find specific event types (O(n))
- **std::min_element/max_element**: Find highest/lowest priority events (O(n))
- **std::count_if**: Count critical events (O(n))

### 6. System Reports & Analytics
- **Reports**: Total events processed, most common emergency type, average response time
- **STL Usage**: Iterators, containers, and algorithm library
- **Analytics**: Event frequency analysis, performance metrics

### 7. File Handling & Persistence
- **Data Files**: `engineers.dat`, `events.dat`, `city_logs.dat`, `config.txt`
- **Operations**: Save/load system state, export logs to CSV
- **File I/O**: Binary serialization for efficiency

## Container Choices & Big-O Analysis

### Vector vs List Justification
- **Vector**: Used for sensor readings requiring fast random access (O(1) access time)
- **List**: Used for historical logs with frequent insertions/deletions (O(1) insertion time)

### Queue vs Stack Justification
- **Queue (FIFO)**: Events processed in order of arrival for fairness
- **Stack (LIFO)**: Emergency overrides processed immediately (most recent first)

## Project Structure
```
NeoVerse_City_System/
├── src/
│   ├── main.cpp              # Main application loop
│   ├── Engineer.h/.cpp       # Authentication system
│   ├── CityData.h/.cpp       # Data management
│   ├── Event.h/.cpp          # Event processing
│   ├── CityZone.h/.cpp       # OOP architecture
│   ├── SystemReports.h/.cpp  # Analytics & reporting
│   └── FileManager.h/.cpp    # Persistence layer
├── data/                     # Data files directory
│   ├── config.txt
│   └── [other data files]
├── build/                    # Build output
├── Makefile                  # Build configuration
└── README.md                 # This file
```

## Sample Usage
1. Login with credentials (admin/admin123)
2. View city sensor data and historical logs
3. Add events and emergency overrides
4. Process events using queue/stack mechanisms
5. Generate system reports
6. Demonstrate polymorphism with city zones
7. Save/load system state to/from files

## Technical Requirements
- C++17 standard
- STL containers and algorithms
- Object-oriented design
- File I/O operations
- Console-based interface
