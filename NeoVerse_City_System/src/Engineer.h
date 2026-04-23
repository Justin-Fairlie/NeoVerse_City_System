#ifndef ENGINEER_H
#define ENGINEER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

enum class ClearanceLevel { LOW, MEDIUM, HIGH };

class Engineer {
private:
    std::string engineerID;
    std::string username;
    std::string encryptedPassword;  
    ClearanceLevel clearanceLevel;

public:
    Engineer(const std::string& id, const std::string& uname, 
             const std::string& pwd, ClearanceLevel level);
    
    // Getters
    std::string getEngineerID() const;
    std::string getUsername() const;
    std::string getEncryptedPassword() const;
    ClearanceLevel getClearanceLevel() const;
    
    // Authentication
    bool authenticate(const std::string& uname, const std::string& pwd) const;
    
    // Password encryption (simple XOR for demonstration)
    static std::string encryptPassword(const std::string& password);
    static std::string decryptPassword(const std::string& encrypted);
    
    // Display
    void display() const;
};

// Authentication System
class AuthSystem {
private:
    std::vector<Engineer> engineers;
    
public:
    AuthSystem();
    void addEngineer(const Engineer& eng);
    bool login(const std::string& username, const std::string& password, ClearanceLevel& level);
    void displayAllEngineers() const;
    
    // Getter for engineers (for persistence)
    const std::vector<Engineer>& getEngineers() const { return engineers; }
    
    // Big-O: Linear search O(n) - suitable for small engineer database
    // Binary search would require sorting which is O(n log n) overhead
    // For n < 100, linear is acceptable
};

#endif