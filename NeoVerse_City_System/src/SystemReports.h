#ifndef SYSTEMREPORTS_H
#define SYSTEMREPORTS_H

#include "Event.h"
#include "CityData.h"
#include <vector>
#include <map>
#include <string>

struct ReportData {
    int totalEventsProcessed;
    std::map<EventType, int> eventTypeCount;
    double averageResponseTime;  // seconds
    double systemLoad;           // 0-100%
    time_t reportTime;
};

class ReportGenerator {
private:
    const EventProcessor& eventProcessor;
    const CityDataManager& dataManager;
    
public:
    ReportGenerator(const EventProcessor& ep, const CityDataManager& dm);
    
    // Generate various reports
    void generateFullReport() const;
    void generateEventSummary() const;
    void generateResourceReport() const;
    void generatePerformanceMetrics() const;
    
    // Analytics using STL algorithms
    EventType getMostCommonEmergency(const std::vector<Event>& events) const;
    double calculateAverageResponseTime(const std::vector<Event>& events) const;
    
    // Export reports
    void exportReportToCSV(const std::string& filename) const;
};

#endif