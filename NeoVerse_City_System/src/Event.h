#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <ctime>

// ADD THIS FORWARD DECLARATION
class CityDataManager;

enum class EventType {
    TRAFFIC_ACCIDENT,
    POWER_FAILURE,
    NETWORK_OVERLOAD,
    WEATHER_ALERT
};

enum class EmergencyLevel {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

struct Event {
    EventType type;
    std::string description;
    time_t timestamp;
    EmergencyLevel emergencyLevel;
    
    void display() const;
    std::string getTypeString() const;
    std::string getEmergencyString() const;
    int getPriorityScore() const;
};

struct EmergencyEvent : public Event {
    std::string overrideCode;
    int responseTeamID;
    
    void displayEmergency() const;
};

struct CompareEventPriority {
    bool operator()(const Event& a, const Event& b) {
        return a.getPriorityScore() < b.getPriorityScore();
    }
};

class EventProcessor {
private:
    std::queue<Event> eventQueue;
    std::stack<EmergencyEvent> emergencyStack;
    std::vector<Event> processedEvents;
    
    // ADD THIS - Pointer to CityDataManager
    CityDataManager* dataManager;
    
public:
    EventProcessor();
    
    // ADD THIS - Setter for CityDataManager
    void setDataManager(CityDataManager* dm);
    
    void addEvent(const Event& e);
    void addEmergency(const EmergencyEvent& ee);
    
    void processNextEvent();
    void processNextEmergency();
    void processAllEvents();
    
    std::vector<Event> filterEventsByType(EventType type) const;
    std::vector<Event> filterEventsByEmergencyLevel(EmergencyLevel level) const;
    
    int getTotalProcessedCount() const;
    std::vector<Event> getProcessedEvents() const;
    
    void displayPendingEvents() const;
    void displayPendingEmergencies() const;
    
    // STL Algorithm demonstrations
    void sortEventsByPriority();  // std::sort
    bool findEventByType(EventType type, Event& foundEvent) const;  // std::find
    int countCriticalEvents() const;  // std::count_if
    Event getHighestPriorityEvent() const;  // std::max_element
    Event getLowestPriorityEvent() const;  // std::min_element
};

#endif