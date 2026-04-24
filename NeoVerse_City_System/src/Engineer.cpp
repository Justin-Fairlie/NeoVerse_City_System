#include "Engineer.h"
#include <fstream>
#include <sstream>

// Simple XOR encryption key
const char ENCRYPTION_KEY = 0x5A;

Engineer::Engineer(const std::string& id, const std::string& uname, 
                   const std::string& pwd, ClearanceLevel level)
    : engineerID(id), username(uname), clearanceLevel(level) {
    encryptedPassword = encryptPassword(pwd);
}

std::string Engineer::getEngineerID() const { return engineerID; }
std::string Engineer::getUsername() const { return username; }
std::string Engineer::getEncryptedPassword() const { return encryptedPassword; }
ClearanceLevel Engineer::getClearanceLevel() const { return clearanceLevel; }

std::string Engineer::encryptPassword(const std::string& password) {
    std::string encrypted = password;
    for (char& c : encrypted) {
        c ^= ENCRYPTION_KEY;
    }
    return encrypted;
}

std::string Engineer::decryptPassword(const std::string& encrypted) {
    std::string decrypted = encrypted;
    for (char& c : decrypted) {
        c ^= ENCRYPTION_KEY;
    }
    return decrypted;
}

bool Engineer::authenticate(const std::string& uname, const std::string& pwd) const {
    return (username == uname && decryptPassword(encryptedPassword) == pwd);
}

void Engineer::display() const {
    std::string levelStr;
    switch(clearanceLevel) {
        case ClearanceLevel::LOW: levelStr = "LOW"; break;
        case ClearanceLevel::MEDIUM: levelStr = "MEDIUM"; break;
        case ClearanceLevel::HIGH: levelStr = "HIGH"; break;
    }
    std::cout << "Engineer ID: " << engineerID 
              << " | Username: " << username 
              << " | Clearance: " << levelStr << std::endl;
    std::cout << "  Encrypted Password: " << encryptedPassword << std::endl;
}

AuthSystem::AuthSystem() {
    // Load default engineers
    addEngineer(Engineer("ENG001", "admin", "admin123", ClearanceLevel::HIGH));
    addEngineer(Engineer("ENG002", "operator", "Operator321!", ClearanceLevel::MEDIUM));
    addEngineer(Engineer("ENG003", "viewer", "View789!", ClearanceLevel::LOW));
}

void AuthSystem::addEngineer(const Engineer& eng) {
    engineers.push_back(eng);
}

// Big-O Complexity: O(n) - Linear search
// Space Complexity: O(1)
// Justification: Small dataset (engineers < 100), 

bool AuthSystem::login(const std::string& username, const std::string& password, 
                       ClearanceLevel& level) {
    auto it = std::find_if(engineers.begin(), engineers.end(),
        [&username, &password](const Engineer& eng) {
            return eng.authenticate(username, password);
        });
    
    if (it != engineers.end()) {
        level = it->getClearanceLevel();
        return true;
    }
    return false;
}

void AuthSystem::displayAllEngineers() const {
    for (const auto& eng : engineers) {
        eng.display();
    }
}