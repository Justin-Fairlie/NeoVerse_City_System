#include "CityData.h"
#include <iomanip>
#include <algorithm>
#include <numeric>

void SensorReading::display() const {
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &timestamp);
    std::cout << "[" << timeStr << "] Zone: " << zone 
              << " | Energy: " << energyUsage << " MW"
              << " | Traffic: " << trafficDensity << " veh/km"
              << " | Population: " << populationDensity << " people/km²" << std::endl;
}

void CityLog::display() const {
    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &timestamp);
    std::cout << "[" << timeStr << "] Event: " << event 
              << " | Severity: " << severity 
              << " | Resolution: " << resolution << std::endl;
}

CityDataManager::CityDataManager() {
    // Initialize with sample data
    time_t now = time(nullptr);
    dailyReadings.push_back({now, 150.5, 45, 2500, "Downtown"});
    dailyReadings.push_back({now - 86400, 120.3, 30, 1800, "Suburb"});
    dailyReadings.push_back({now - 172800, 180.7, 60, 3000, "Industrial"});
    
    // ADD SAMPLE HISTORICAL LOGS
    CityLog log1;
    log1.timestamp = now;
    log1.event = "System Initialized";
    log1.severity = "INFO";
    log1.resolution = "City monitoring systems online";
    historicalLogs.push_back(log1);
    
    CityLog log2;
    log2.timestamp = now - 3600;
    log2.event = "Power Grid Check";
    log2.severity = "NORMAL";
    log2.resolution = "All systems nominal";
    historicalLogs.push_back(log2);
    
    CityLog log3;
    log3.timestamp = now - 7200;
    log3.event = "Traffic Sensor Calibration";
    log3.severity = "COMPLETED";
    log3.resolution = "Sensors calibrated successfully";
    historicalLogs.push_back(log3);
}

void CityDataManager::addSensorReading(const SensorReading& reading) {
    dailyReadings.push_back(reading);  // Amortized O(1)
}

void CityDataManager::removeOldReadings(int daysToKeep) {
    time_t cutoff = time(nullptr) - (daysToKeep * 86400);
    dailyReadings.erase(
        std::remove_if(dailyReadings.begin(), dailyReadings.end(),
            [cutoff](const SensorReading& r) { return r.timestamp < cutoff; }),
        dailyReadings.end()
    );  // O(n)
}

void CityDataManager::displayAllReadings() const {
    for (const auto& reading : dailyReadings) {
        reading.display();
    }
}

SensorReading& CityDataManager::getReading(int index) {
    return dailyReadings[index];  // O(1) - vector advantage
}

void CityDataManager::addHistoricalLog(const CityLog& log) {
    historicalLogs.push_back(log);  // O(1) - list advantage for unbounded growth
}

void CityDataManager::trimHistoricalLogs(size_t maxSize) {
    while (historicalLogs.size() > maxSize) {
        historicalLogs.pop_front();  // O(1)
    }
}

void CityDataManager::displayAllLogs() const {
    for (const auto& log : historicalLogs) {
        log.display();
    }
}

double CityDataManager::getAverageEnergyUsage() const {
    if (dailyReadings.empty()) return 0.0;
    double sum = std::accumulate(dailyReadings.begin(), dailyReadings.end(), 0.0,
        [](double acc, const SensorReading& r) { return acc + r.energyUsage; });
    return sum / dailyReadings.size();
}

int CityDataManager::getAverageTrafficDensity() const {
    if (dailyReadings.empty()) return 0;
    int sum = std::accumulate(dailyReadings.begin(), dailyReadings.end(), 0,
        [](int acc, const SensorReading& r) { return acc + r.trafficDensity; });
    return sum / dailyReadings.size();
}