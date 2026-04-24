#ifndef CITYDATA_H
#define CITYDATA_H

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <ctime>

struct SensorReading {
    time_t timestamp;
    double energyUsage;      
    int trafficDensity;      
    double populationDensity; 
    std::string zone;
    
    void display() const;
};

struct CityLog {
    time_t timestamp;
    std::string event;
    std::string severity;
    std::string resolution;
    
    void display() const;
};

class CityDataManager {
private:
    std::vector<SensorReading> dailyReadings;    // Fast random access O(1)
    std::list<CityLog> historicalLogs;            // Unbounded growth O(1) insertion
    
public:
    CityDataManager();
    
    // Vector operations
    void addSensorReading(const SensorReading& reading);  // Amortized O(1)
    void removeOldReadings(int daysToKeep);               // O(n)
    void displayAllReadings() const;                      // O(n)
    SensorReading& getReading(int index);                 // O(1) - vector advantage
    
    // List operations
    void addHistoricalLog(const CityLog& log);            // O(1) - list advantage
    void trimHistoricalLogs(size_t maxSize);                 // O(n)
    void displayAllLogs() const;                          // O(n)
    
    // Analytics
    double getAverageEnergyUsage() const;
    int getAverageTrafficDensity() const;
    
    // Getter for logs (for persistence)
    const std::list<CityLog>& getHistoricalLogs() const { return historicalLogs; }
    
    // Big-O Analysis:
    // Vector: 
    //   - Access: O(1) - contiguous memory
    //   - Insert at end: Amortized O(1)
    //   - Insert at middle: O(n)
    //   - Delete: O(n)
    // List:
    //   - Access: O(n) - sequential only
    //   - Insert anywhere: O(1) with iterator
    //   - Delete: O(1) with iterator
    //   - It's Suitable for unbounded logs due to dynamic node allocation
};

#endif