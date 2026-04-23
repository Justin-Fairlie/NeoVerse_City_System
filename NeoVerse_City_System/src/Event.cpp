#include "Event.h"
#include <iostream>
#include <iomanip>
#include "CityData.h"


void Event::display() const {
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &timestamp);
    std::cout << "[" << timeStr << "] Type: " << getTypeString()
              << " | Emergency: " << getEmergencyString()
              << " | " << description << std::endl;
}

std::string Event::getTypeString() const {
    switch(type) {
        case EventType::TRAFFIC_ACCIDENT: return "TRAFFIC_ACCIDENT";
        case EventType::POWER_FAILURE: return "POWER_FAILURE";
        case EventType::NETWORK_OVERLOAD: return "NETWORK_OVERLOAD";
        case EventType::WEATHER_ALERT: return "WEATHER_ALERT";
        default: return "UNKNOWN";
    }
}

std::string Event::getEmergencyString() const {
    switch(emergencyLevel) {
        case EmergencyLevel::LOW: return "LOW";
        case EmergencyLevel::MEDIUM: return "MEDIUM";
        case EmergencyLevel::HIGH: return "HIGH";
        case EmergencyLevel::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

int Event::getPriorityScore() const {
    // Higher score = higher priority
    switch(emergencyLevel) {
        case EmergencyLevel::CRITICAL: return 100;
        case EmergencyLevel::HIGH: return 75;
        case EmergencyLevel::MEDIUM: return 50;
        case EmergencyLevel::LOW: return 25;
        default: return 0;
    }
}

void EmergencyEvent::displayEmergency() const {
    display();
    std::cout << "  >> Override Code: " << overrideCode 
              << " | Response Team: " << responseTeamID << std::endl;
}

EventProcessor::EventProcessor() : dataManager(nullptr) {}

void EventProcessor::setDataManager(CityDataManager* dm) {
    dataManager = dm;
}

void EventProcessor::addEvent(const Event& e) {
    eventQueue.push(e);
}

void EventProcessor::addEmergency(const EmergencyEvent& ee) {
    emergencyStack.push(ee);
}

void EventProcessor::processNextEvent() {
    if (!eventQueue.empty()) {
        Event e = eventQueue.front();
        eventQueue.pop();
        processedEvents.push_back(e);
        std::cout << "Processing event: ";
        e.display();
    }
}

void EventProcessor::processNextEmergency() {
    if (!emergencyStack.empty()) {
        EmergencyEvent ee = emergencyStack.top();
        emergencyStack.pop();
        processedEvents.push_back(ee);
        std::cout << "EMERGENCY OVERRIDE: ";
        ee.displayEmergency();
    }
}

void EventProcessor::processAllEvents() {
    // Process emergencies first (they're on stack for immediate handling)
    while (!emergencyStack.empty()) {
        processNextEmergency();
    }
    // Then process regular events in order
    while (!eventQueue.empty()) {
        processNextEvent();
    }
}

std::vector<Event> EventProcessor::filterEventsByType(EventType type) const {
    std::vector<Event> result;
    // Create temp queue for iteration (preserving original)
    std::queue<Event> tempQueue = eventQueue;
    while (!tempQueue.empty()) {
        Event e = tempQueue.front();
        if (e.type == type) {
            result.push_back(e);
        }
        tempQueue.pop();
    }
    return result;
}

std::vector<Event> EventProcessor::filterEventsByEmergencyLevel(EmergencyLevel level) const {
    std::vector<Event> result;
    std::queue<Event> tempQueue = eventQueue;
    while (!tempQueue.empty()) {
        Event e = tempQueue.front();
        if (e.emergencyLevel == level) {
            result.push_back(e);
        }
        tempQueue.pop();
    }
    return result;
}

int EventProcessor::getTotalProcessedCount() const {
    return processedEvents.size();
}

std::vector<Event> EventProcessor::getProcessedEvents() const {
    return processedEvents;
}

void EventProcessor::displayPendingEvents() const {
    std::queue<Event> tempQueue = eventQueue;
    if (tempQueue.empty()) {
        std::cout << "No pending events." << std::endl;
        return;
    }
    std::cout << "\n--- PENDING EVENTS (FIFO Queue) ---" << std::endl;
    while (!tempQueue.empty()) {
        tempQueue.front().display();
        tempQueue.pop();
    }
}

void EventProcessor::displayPendingEmergencies() const {
    std::stack<EmergencyEvent> tempStack = emergencyStack;
    if (tempStack.empty()) {
        std::cout << "No pending emergencies." << std::endl;
        return;
    }
    std::cout << "\n--- PENDING EMERGENCIES (LIFO Stack) ---" << std::endl;
    while (!tempStack.empty()) {
        tempStack.top().displayEmergency();
        tempStack.pop();
    }
}

// STL Algorithm demonstrations
void EventProcessor::sortEventsByPriority() {
    // Convert queue to vector for sorting (since queue doesn't support random access)
    std::vector<Event> tempEvents;
    std::queue<Event> tempQueue = eventQueue;
    while (!tempQueue.empty()) {
        tempEvents.push_back(tempQueue.front());
        tempQueue.pop();
    }
    
    // Sort by priority score (highest first) - O(n log n)
    std::sort(tempEvents.begin(), tempEvents.end(), CompareEventPriority());
    
    // Rebuild queue in sorted order
    eventQueue = std::queue<Event>();
    for (const auto& event : tempEvents) {
        eventQueue.push(event);
    }
    
    std::cout << "Events sorted by priority (highest first)" << std::endl;
}

bool EventProcessor::findEventByType(EventType type, Event& foundEvent) const {
    // Create temp queue for searching
    std::queue<Event> tempQueue = eventQueue;
    
    // Find first event of specified type - O(n)
    while (!tempQueue.empty()) {
        Event e = tempQueue.front();
        tempQueue.pop();
        if (e.type == type) {
            foundEvent = e;
            return true;
        }
    }
    return false;
}

int EventProcessor::countCriticalEvents() const {
    // Count events with CRITICAL emergency level - O(n)
    std::queue<Event> tempQueue = eventQueue;
    int count = 0;
    while (!tempQueue.empty()) {
        if (tempQueue.front().emergencyLevel == EmergencyLevel::CRITICAL) {
            count++;
        }
        tempQueue.pop();
    }
    return count;
}

Event EventProcessor::getHighestPriorityEvent() const {
    if (eventQueue.empty()) {
        return Event{EventType::TRAFFIC_ACCIDENT, "No events", 0, EmergencyLevel::LOW};
    }
    
    // Find event with highest priority score - O(n)
    std::queue<Event> tempQueue = eventQueue;
    Event highest = tempQueue.front();
    tempQueue.pop();
    
    while (!tempQueue.empty()) {
        Event current = tempQueue.front();
        if (CompareEventPriority()(highest, current)) {
            highest = current;
        }
        tempQueue.pop();
    }
    return highest;
}

Event EventProcessor::getLowestPriorityEvent() const {
    if (eventQueue.empty()) {
        return Event{EventType::TRAFFIC_ACCIDENT, "No events", 0, EmergencyLevel::LOW};
    }
    
    // Find event with lowest priority score - O(n)
    std::queue<Event> tempQueue = eventQueue;
    Event lowest = tempQueue.front();
    tempQueue.pop();
    
    while (!tempQueue.empty()) {
        Event current = tempQueue.front();
        if (CompareEventPriority()(current, lowest)) {
            lowest = current;
        }
        tempQueue.pop();
    }
    return lowest;
}