#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Engineer.h"
#include "Event.h"
#include "CityData.h"
#include <string>
#include <vector>

class FileManager {
public:
    // Save/Load engineers
    static bool saveEngineers(const std::vector<Engineer>& engineers, const std::string& filename);
    static bool loadEngineers(std::vector<Engineer>& engineers, const std::string& filename);
    
    // Save/Load events
    static bool saveEvents(const std::vector<Event>& events, const std::string& filename);
    static bool loadEvents(std::vector<Event>& events, const std::string& filename);
    
    // Save/Load city logs
    static bool saveCityLogs(const std::list<CityLog>& logs, const std::string& filename);
    static bool loadCityLogs(std::list<CityLog>& logs, const std::string& filename);
    
    // Configuration management
    static bool saveConfig(const std::string& key, const std::string& value, const std::string& filename);
    static std::string loadConfig(const std::string& key, const std::string& filename);
    
    // Export logs to CSV
    static void exportLogsToCSV(const std::list<CityLog>& logs, const std::string& filename);
};

#endif