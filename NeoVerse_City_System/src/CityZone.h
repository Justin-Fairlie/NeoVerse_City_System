#ifndef CITYZONE_H
#define CITYZONE_H

#include <string>
#include <iostream>

// Base class demonstrating polymorphism
class CityZone {
protected:
    std::string zoneName;
    int population;
    double energyConsumption;
    
public:
    CityZone(const std::string& name, int pop, double energy);
    virtual ~CityZone();
    
    // Virtual function for polymorphism
    virtual void processEvent(const std::string& event) = 0;  // Pure virtual
    virtual void displayStatus() const;
    virtual double getEfficiencyScore() const;
    
    // Getters/Setters (encapsulation)
    std::string getZoneName() const;
    void setZoneName(const std::string& name);
    int getPopulation() const;
    void setPopulation(int pop);
    double getEnergyConsumption() const;
    void setEnergyConsumption(double energy);
};

// Derived class 1
class ResidentialZone : public CityZone {
private:
    int numberOfHouses;
    double averageHouseholdEnergy;
    
public:
    ResidentialZone(const std::string& name, int pop, double energy, int houses, double avgEnergy);
    
    void processEvent(const std::string& event) override;
    void displayStatus() const override;
    double getEfficiencyScore() const override;
};

// Derived class 2
class IndustrialZone : public CityZone {
private:
    int numberOfFactories;
    double carbonEmission;
    
public:
    IndustrialZone(const std::string& name, int pop, double energy, int factories, double carbon);
    
    void processEvent(const std::string& event) override;
    void displayStatus() const override;
    double getEfficiencyScore() const override;
};

// Derived class 3
class CommercialZone : public CityZone {
private:
    int numberOfBusinesses;
    double revenuePerDay;
    
public:
    CommercialZone(const std::string& name, int pop, double energy, int businesses, double revenue);
    
    void processEvent(const std::string& event) override;
    void displayStatus() const override;
    double getEfficiencyScore() const override;
};

#endif