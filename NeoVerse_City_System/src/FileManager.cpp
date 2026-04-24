#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool FileManager::saveEngineers(const std::vector<Engineer>& engineers, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    size_t count = engineers.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& eng : engineers) {
        
        // Just save the essential data
        std::string id = eng.getEngineerID();
        std::string username = eng.getUsername();
        std::string pwd = eng.getEncryptedPassword();
        ClearanceLevel level = eng.getClearanceLevel();
        
        size_t len = id.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(id.c_str(), len);
        
        len = username.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(username.c_str(), len);
        
        len = pwd.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(pwd.c_str(), len);
        
        file.write(reinterpret_cast<const char*>(&level), sizeof(level));
    }
    
    file.close();
    std::cout << "Engineers saved to " << filename << std::endl;
    return true;
}

bool FileManager::loadEngineers(std::vector<Engineer>& engineers, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    engineers.clear();
    for (size_t i = 0; i < count; i++) {
        size_t len;
        std::string id, username, pwd;
        ClearanceLevel level;
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        id.resize(len);
        file.read(&id[0], len);
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        username.resize(len);
        file.read(&username[0], len);
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        pwd.resize(len);
        file.read(&pwd[0], len);
        
        file.read(reinterpret_cast<char*>(&level), sizeof(level));
        
        engineers.emplace_back(id, username, Engineer::decryptPassword(pwd), level);
    }
    
    file.close();
    std::cout << "Engineers loaded from " << filename << std::endl;
    return true;
}

bool FileManager::saveEvents(const std::vector<Event>& events, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    size_t count = events.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& e : events) {
        file.write(reinterpret_cast<const char*>(&e.type), sizeof(e.type));
        size_t len = e.description.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(e.description.c_str(), len);
        file.write(reinterpret_cast<const char*>(&e.timestamp), sizeof(e.timestamp));
        file.write(reinterpret_cast<const char*>(&e.emergencyLevel), sizeof(e.emergencyLevel));
    }
    
    file.close();
    std::cout << "Events saved to " << filename << std::endl;
    return true;
}

bool FileManager::loadEvents(std::vector<Event>& events, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    events.clear();
    for (size_t i = 0; i < count; i++) {
        Event e;
        size_t len;
        file.read(reinterpret_cast<char*>(&e.type), sizeof(e.type));
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        e.description.resize(len);
        file.read(&e.description[0], len);
        file.read(reinterpret_cast<char*>(&e.timestamp), sizeof(e.timestamp));
        file.read(reinterpret_cast<char*>(&e.emergencyLevel), sizeof(e.emergencyLevel));
        events.push_back(e);
    }
    
    file.close();
    std::cout << "Events loaded from " << filename << std::endl;
    return true;
}

bool FileManager::saveCityLogs(const std::list<CityLog>& logs, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    size_t count = logs.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (const auto& log : logs) {
        file.write(reinterpret_cast<const char*>(&log.timestamp), sizeof(log.timestamp));
        
        size_t len = log.event.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(log.event.c_str(), len);
        
        len = log.severity.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(log.severity.c_str(), len);
        
        len = log.resolution.length();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(log.resolution.c_str(), len);
    }
    
    file.close();
    std::cout << "City logs saved to " << filename << std::endl;
    return true;
}

bool FileManager::loadCityLogs(std::list<CityLog>& logs, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    logs.clear();
    for (size_t i = 0; i < count; i++) {
        CityLog log;
        size_t len;
        
        file.read(reinterpret_cast<char*>(&log.timestamp), sizeof(log.timestamp));
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        log.event.resize(len);
        file.read(&log.event[0], len);
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        log.severity.resize(len);
        file.read(&log.severity[0], len);
        
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        log.resolution.resize(len);
        file.read(&log.resolution[0], len);
        
        logs.push_back(log);
    }
    
    file.close();
    std::cout << "City logs loaded from " << filename << std::endl;
    return true;
}

bool FileManager::saveConfig(const std::string& key, const std::string& value, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) return false;
    
    file << key << "=" << value << "\n";
    file.close();
    return true;
}

std::string FileManager::loadConfig(const std::string& key, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return "";
    
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string fileKey = line.substr(0, pos);
            if (fileKey == key) {
                return line.substr(pos + 1);
            }
        }
    }
    
    return "";
}

void FileManager::exportLogsToCSV(const std::list<CityLog>& logs, const std::string& filename) {
    std::cout << "Attempting to export to: " << filename << std::endl;
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }
    
    file << "Timestamp,Event,Severity,Resolution\n";
    for (const auto& log : logs) {
        file << log.timestamp << "," 
             << log.event << ","
             << log.severity << ","
             << log.resolution << "\n";
    }
    
    file.close();
    std::cout << "Logs exported to CSV: " << filename << std::endl;
}