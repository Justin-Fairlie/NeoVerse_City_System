#include "SystemReports.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>

ReportGenerator::ReportGenerator(const EventProcessor& ep, const CityDataManager& dm)
    : eventProcessor(ep), dataManager(dm) {}

void ReportGenerator::generateFullReport() const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "            NEOVERSE CITY SYSTEM REPORT" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    generateEventSummary();
    generateResourceReport();
    generatePerformanceMetrics();
    
    std::cout << std::string(60, '=') << std::endl;
}

void ReportGenerator::generateEventSummary() const {
    std::cout << "\n--- EVENT SUMMARY ---" << std::endl;
    std::cout << "Total Events Processed: " << eventProcessor.getTotalProcessedCount() << std::endl;
    
    auto processedEvents = eventProcessor.getProcessedEvents();
    if (!processedEvents.empty()) {
        EventType mostCommon = getMostCommonEmergency(processedEvents);
        std::cout << "Most Common Event Type: ";
        switch(mostCommon) {
            case EventType::TRAFFIC_ACCIDENT: std::cout << "Traffic Accident"; break;
            case EventType::POWER_FAILURE: std::cout << "Power Failure"; break;
            case EventType::NETWORK_OVERLOAD: std::cout << "Network Overload"; break;
            case EventType::WEATHER_ALERT: std::cout << "Weather Alert"; break;
        }
        std::cout << std::endl;
        
        double avgResponse = calculateAverageResponseTime(processedEvents);
        std::cout << "Average Response Time: " << std::fixed << std::setprecision(2) 
                  << avgResponse << " seconds" << std::endl;
    }
}

void ReportGenerator::generateResourceReport() const {
    std::cout << "\n--- RESOURCE REPORT ---" << std::endl;
    std::cout << "Average Energy Usage: " << std::fixed << std::setprecision(2)
              << dataManager.getAverageEnergyUsage() << " MW" << std::endl;
    std::cout << "Average Traffic Density: " << dataManager.getAverageTrafficDensity() 
              << " vehicles/km" << std::endl;
}

void ReportGenerator::generatePerformanceMetrics() const {
    std::cout << "\n--- PERFORMANCE METRICS ---" << std::endl;
    std::cout << "System Load: " << (eventProcessor.getTotalProcessedCount() / 100.0) << "%" << std::endl;
}

EventType ReportGenerator::getMostCommonEmergency(const std::vector<Event>& events) const {
    std::map<EventType, int> countMap;
    for (const auto& event : events) {
        countMap[event.type]++;
    }
    
    auto maxIt = std::max_element(countMap.begin(), countMap.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    
    return maxIt != countMap.end() ? maxIt->first : EventType::TRAFFIC_ACCIDENT;
}

double ReportGenerator::calculateAverageResponseTime(const std::vector<Event>& events) const {
    if (events.empty()) return 0.0;
    
    // Simulate response time calculation
    double totalTime = std::accumulate(events.begin(), events.end(), 0.0,
        [](double sum, const Event& e) {
            // Simulated response time based on priority
            return sum + (10.0 / (e.getPriorityScore() + 1));
        });
    
    return totalTime / events.size();
}

void ReportGenerator::exportReportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }
    
    file << "Report Type,Value,Timestamp\n";
    file << "Total Events Processed," << eventProcessor.getTotalProcessedCount() << "," << time(nullptr) << "\n";
    file << "Average Energy Usage," << dataManager.getAverageEnergyUsage() << "," << time(nullptr) << "\n";
    file << "Average Traffic Density," << dataManager.getAverageTrafficDensity() << "," << time(nullptr) << "\n";
    
    file.close();
    std::cout << "Report exported to " << filename << std::endl;
}