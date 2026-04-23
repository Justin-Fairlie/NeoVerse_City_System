#include "Engineer.h"
#include "CityData.h"
#include "Event.h"
#include "CityZone.h"
#include "SystemReports.h"
#include "FileManager.h"
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

void displayMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "     NEOVERSE AI CITY SURVIVAL SYSTEM" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. View City Sensor Data" << std::endl;
    std::cout << "2. View Historical Logs" << std::endl;
    std::cout << "3. Add New Event" << std::endl;
    std::cout << "4. Add Emergency Override" << std::endl;
    std::cout << "5. Process Events" << std::endl;
    std::cout << "6. Display Pending Events/Emergencies" << std::endl;
    std::cout << "7. Generate System Report" << std::endl;
    std::cout << "8. Demonstrate Polymorphism (City Zones)" << std::endl;
    std::cout << "9. Demonstrate STL Algorithms" << std::endl;
    std::cout << "10. Save System State" << std::endl;
    std::cout << "11. Load System State" << std::endl;
    std::cout << "12. Export Logs to CSV" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choice: ";
}

// This function demonstrates POLYMORPHISM - one of the main C++ concepts
// Polymorphism means one function/object can work with different derived classes
void demonstratePolymorphism() {
    std::cout << "\n--- POLYMORPHISM DEMONSTRATION ---" << std::endl;
    
    // Create a vector to store different types of zones (Residential, Industrial, Commercial)
    // We can store them in a vector of base class pointers (CityZone)
    std::vector<std::unique_ptr<CityZone>> zones;
    
    // Add three different types of zones - all inheriting from CityZone base class
    zones.push_back(std::make_unique<ResidentialZone>("Green Acres", 50000, 120.5, 15000, 0.008));
    zones.push_back(std::make_unique<IndustrialZone>("Tech Valley", 20000, 350.8, 45, 520.3));
    zones.push_back(std::make_unique<CommercialZone>("Downtown Core", 30000, 280.3, 1200, 2500000));
    
    // Define different events to test
    std::string events[] = {"POWER_FAILURE", "WEATHER_ALERT", "NETWORK_OVERLOAD", "TRAFFIC_ACCIDENT"};
    
    // Loop through each zone and process the events
    // POLYMORPHISM: Same function call (processEvent) but different behavior for each zone type!
    for (auto& zone : zones) {
        zone->displayStatus();  // Show zone information
        for (const auto& event : events) {
            zone->processEvent(event);  // Each zone handles events differently!
        }
        std::cout << "Efficiency Score: " << zone->getEfficiencyScore() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

// Main entry point of the program
int main() {
    std::cout << "=== NEOVERSE AI CITY SURVIVAL SYSTEM ===" << std::endl;
    std::cout << "Initializing system components...\n" << std::endl;
    
    // Create all the main system objects:
    // - AuthSystem: handles login and security
    // - CityDataManager: stores sensor readings and logs (uses vector and list)
    // - EventProcessor: manages events in queue and emergencies in stack
    // - ReportGenerator: creates system reports and statistics
    AuthSystem auth;
    CityDataManager dataManager;
    EventProcessor eventProcessor;
    ReportGenerator reportGenerator(eventProcessor, dataManager);
    
    // Give the event processor a reference to the data manager so it can store logs
    eventProcessor.setDataManager(&dataManager);
    
    // Authentication section - user must login to access the system
    std::string username, password;
    ClearanceLevel userLevel;
    bool authenticated = false;
    int loginAttempts = 0;
    
    // Try to login, but only allow 3 failed attempts for security
    while (!authenticated && loginAttempts < 3) {
        std::cout << "\n=== AI ENGINEER LOGIN ===" << std::endl;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
        
        // Check if login is correct
        if (auth.login(username, password, userLevel)) {
            authenticated = true;
            std::cout << "\n Login successful! Welcome, " << username << std::endl;
            std::cout << "Clearance Level: ";
            // Display the user's clearance level
            switch(userLevel) {
                case ClearanceLevel::LOW: std::cout << "LOW"; break;
                case ClearanceLevel::MEDIUM: std::cout << "MEDIUM"; break;
                case ClearanceLevel::HIGH: std::cout << "HIGH"; break;
            }
            std::cout << std::endl;
        } else {
            loginAttempts++;
            std::cout << "Login failed! Attempts remaining: " << (3 - loginAttempts) << std::endl;
        }
    }
    
    // If login failed 3 times, exit the program
    if (!authenticated) {
        std::cout << "Too many failed attempts. Exiting system." << std::endl;
        return 1;
    }
    
    // Load some sample data into the system to demonstrate functionality
    // These events will be stored in a QUEUE (First In, First Out)
    std::cout << "\nLoading sample city data..." << std::endl;
    eventProcessor.addEvent({EventType::TRAFFIC_ACCIDENT, "Accident on Highway 101", time(nullptr), EmergencyLevel::HIGH});
    eventProcessor.addEvent({EventType::POWER_FAILURE, "Transformer explosion in Sector 7", time(nullptr), EmergencyLevel::CRITICAL});
    eventProcessor.addEvent({EventType::WEATHER_ALERT, "Severe thunderstorm approaching", time(nullptr), EmergencyLevel::MEDIUM});
    
    // Add a critical emergency - these go to a STACK (Last In, First Out)
    EmergencyEvent ee;
    ee.type = EventType::NETWORK_OVERLOAD;
    ee.description = "Core network router failure";
    ee.timestamp = time(nullptr);
    ee.emergencyLevel = EmergencyLevel::CRITICAL;
    ee.overrideCode = "EMERG-OVR-001";
    ee.responseTeamID = 42;
    eventProcessor.addEmergency(ee);
    
    // START THE MAIN MENU LOOP
    // This loop keeps the program running until the user selects "Exit" (option 0)
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        
        switch(choice) {
            // OPTION 1: Show all sensor data stored in vector
            case 1:
                std::cout << "\n--- SENSOR READINGS ---" << std::endl;
                dataManager.displayAllReadings();
                break;
            
            // OPTION 2: Show all historical logs stored in list    
            case 2:
                std::cout << "\n--- HISTORICAL LOGS ---" << std::endl;
                dataManager.displayAllLogs();
                break;
            
            // OPTION 3: Add a new event to the queue    
            case 3: {
                std::cout << "\n--- ADD NEW EVENT ---" << std::endl;
                int typeChoice, levelChoice;
                std::string desc;
                
                std::cout << "Event Type (1-Traffic, 2-Power, 3-Network, 4-Weather): ";
                std::cin >> typeChoice;
                std::cout << "Emergency Level (1-Low, 2-Medium, 3-High, 4-Critical): ";
                std::cin >> levelChoice;
                std::cin.ignore();
                std::cout << "Description: ";
                std::getline(std::cin, desc);
                
                Event e;
                e.type = static_cast<EventType>(typeChoice - 1);
                e.description = desc;
                e.timestamp = time(nullptr);
                e.emergencyLevel = static_cast<EmergencyLevel>(levelChoice - 1);
                
                eventProcessor.addEvent(e);
                std::cout << " Event added successfully!" << std::endl;
                break;
            }
            
            // OPTION 4: Add an emergency override (goes to stack)    
            case 4: {
                std::cout << "\n--- ADD EMERGENCY OVERRIDE ---" << std::endl;
                EmergencyEvent ee;
                int typeChoice, levelChoice;
                std::string desc, code;
                
                std::cout << "Event Type (1-Traffic, 2-Power, 3-Network, 4-Weather): ";
                std::cin >> typeChoice;
                std::cout << "Emergency Level (1-Low, 2-Medium, 3-High, 4-Critical): ";
                std::cin >> levelChoice;
                std::cin.ignore();
                std::cout << "Description: ";
                std::getline(std::cin, desc);
                std::cout << "Override Code: ";
                std::getline(std::cin, code);
                std::cout << "Response Team ID: ";
                std::cin >> ee.responseTeamID;
                
                ee.type = static_cast<EventType>(typeChoice - 1);
                ee.description = desc;
                ee.timestamp = time(nullptr);
                ee.emergencyLevel = static_cast<EmergencyLevel>(levelChoice - 1);
                ee.overrideCode = code;
                
                eventProcessor.addEmergency(ee);
                std::cout << " EMERGENCY OVERRIDE added! Will be processed immediately!" << std::endl;
                break;
            }
            
            // OPTION 5: Process all events from the queue (one at a time, FIFO)    
            case 5:
                std::cout << "\n--- PROCESSING EVENTS ---" << std::endl;
                eventProcessor.processAllEvents();
                std::cout << "All events processed!" << std::endl;
                break;
            
            // OPTION 6: Show what events are waiting to be processed    
            case 6:
                eventProcessor.displayPendingEvents();
                eventProcessor.displayPendingEmergencies();
                break;
            
            // OPTION 7: Generate a detailed report of the entire system    
            case 7:
                reportGenerator.generateFullReport();
                break;
            
            // OPTION 8: Demonstrate POLYMORPHISM - same code, different behavior    
            case 8:
                demonstratePolymorphism();
                break;
            
            // OPTION 9: Demonstrate STL ALGORITHMS - sort, find, count, min, max    
            case 9: {
                std::cout << "\n--- STL ALGORITHMS DEMONSTRATION ---" << std::endl;
                
                // STL ALGORITHM 1: std::sort - arranges events by priority
                std::cout << "Sorting events by priority..." << std::endl;
                eventProcessor.sortEventsByPriority();
                
                // STL ALGORITHM 2: std::find_if - searches for a specific event type
                std::cout << "Finding first TRAFFIC_ACCIDENT event..." << std::endl;
                Event foundEvent;
                if (eventProcessor.findEventByType(EventType::TRAFFIC_ACCIDENT, foundEvent)) {
                    std::cout << "Found: ";
                    foundEvent.display();
                } else {
                    std::cout << "No TRAFFIC_ACCIDENT events found." << std::endl;
                }
                
                // STL ALGORITHM 3: std::count_if - counts how many critical events exist
                std::cout << "Counting CRITICAL events: " << eventProcessor.countCriticalEvents() << std::endl;
                
                // STL ALGORITHM 4: std::max_element - finds the event with highest priority
                std::cout << "Highest priority event: ";
                eventProcessor.getHighestPriorityEvent().display();
                
                // STL ALGORITHM 5: std::min_element - finds the event with lowest priority
                std::cout << "Lowest priority event: ";
                eventProcessor.getLowestPriorityEvent().display();
                break;
            }
            
            // OPTION 10: Save all system data to files (engineers, events, logs, config)    
            case 10: {
                std::cout << "\n--- SAVING SYSTEM STATE ---" << std::endl;
                // Save engineers
                const auto& engineers = auth.getEngineers();
                FileManager::saveEngineers(engineers, "data/engineers.dat");
                // Save configuration
                FileManager::saveConfig("last_save", std::to_string(time(nullptr)), "data/config.txt");
                // Save processed events
                std::vector<Event> processedEvts = eventProcessor.getProcessedEvents();
                FileManager::saveEvents(processedEvts, "data/events.dat");
                // Save city logs
                const auto& logs = dataManager.getHistoricalLogs();
                FileManager::saveCityLogs(logs, "data/city_logs.dat");
                std::cout << "System state saved to data/ directory" << std::endl;
                break;
            }
            
            // OPTION 11: Load all system data from files (engineers, events, logs)    
            case 11: {
                std::cout << "\n--- LOADING SYSTEM STATE ---" << std::endl;
                // Load engineers
                std::vector<Engineer> loadedEngineers;
                if (FileManager::loadEngineers(loadedEngineers, "data/engineers.dat")) {
                    std::cout << "Engineers loaded: " << loadedEngineers.size() << " entries" << std::endl;
                }
                // Load city logs
                std::list<CityLog> loadedLogs;
                if (FileManager::loadCityLogs(loadedLogs, "data/city_logs.dat")) {
                    std::cout << "City logs loaded: " << loadedLogs.size() << " entries" << std::endl;
                }
                // Load events
                std::vector<Event> loadedEvents;
                if (FileManager::loadEvents(loadedEvents, "data/events.dat")) {
                    std::cout << "Events loaded: " << loadedEvents.size() << " entries" << std::endl;
                }
                std::cout << "System state loaded from data/ directory" << std::endl;
                break;
            }
            
            // OPTION 12: Export the logs to a CSV file (can be opened in Excel)    
            case 12: {
                std::cout << "\n--- EXPORT LOGS TO CSV ---" << std::endl;
                // Create sample logs
                std::list<CityLog> logs;
                logs.push_back({time(nullptr), "System Startup", "INFO", "Completed"});
                logs.push_back({time(nullptr), "Power Fluctuation", "WARNING", "Stabilized"});
                FileManager::exportLogsToCSV(logs, "data/city_logs_export.csv");
                break;
            }
            
            // OPTION 0: Exit the program gracefully    
            case 0:
                std::cout << "\nShutting down NeoVerse City System..." << std::endl;
                std::cout << "Goodbye, Engineer " << username << "!" << std::endl;
                break;
            
            // Handle invalid input    
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        
        // After each menu choice (except exit), wait for user to press Enter
        // This gives the user time to read the output before showing the menu again
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 0);  // Keep showing menu until user selects "Exit" (0)
    
    return 0;  // Program finished successfully
}