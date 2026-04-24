#include "CityZone.h"
#include <cmath>

// The Base class implementation
CityZone::CityZone(const std::string& name, int pop, double energy)
    : zoneName(name), population(pop), energyConsumption(energy) {
    std::cout << "CityZone [" << zoneName << "] constructed." << std::endl;
}

CityZone::~CityZone() {
    std::cout << "CityZone [" << zoneName << "] destroyed." << std::endl;
}

void CityZone::displayStatus() const {
    std::cout << "Zone: " << zoneName 
              << " | Population: " << population
              << " | Energy: " << energyConsumption << " MW";
}

double CityZone::getEfficiencyScore() const {
    // Base efficiency: energy per capita
    if (population > 0) {
        return energyConsumption / population;
    }
    return 0;
}

std::string CityZone::getZoneName() const { return zoneName; }
void CityZone::setZoneName(const std::string& name) { zoneName = name; }
int CityZone::getPopulation() const { return population; }
void CityZone::setPopulation(int pop) { population = pop; }
double CityZone::getEnergyConsumption() const { return energyConsumption; }
void CityZone::setEnergyConsumption(double energy) { energyConsumption = energy; }

// ResidentialZone implementation
ResidentialZone::ResidentialZone(const std::string& name, int pop, double energy, 
                                 int houses, double avgEnergy)
    : CityZone(name, pop, energy), numberOfHouses(houses), averageHouseholdEnergy(avgEnergy) {}

void ResidentialZone::processEvent(const std::string& event) {
    std::cout << "[RESIDENTIAL] " << zoneName << " processing: " << event;
    if (event == "POWER_FAILURE") {
        std::cout << " - Activating backup generators for " << numberOfHouses << " homes!";
    } else if (event == "WEATHER_ALERT") {
        std::cout << " - Issuing evacuation warnings to residents!";
    }
    std::cout << std::endl;
}

void ResidentialZone::displayStatus() const {
    CityZone::displayStatus();
    std::cout << " | Houses: " << numberOfHouses
              << " | Avg Household Energy: " << averageHouseholdEnergy << " MW" << std::endl;
}

double ResidentialZone::getEfficiencyScore() const {
    double baseScore = CityZone::getEfficiencyScore();
    // Residential zones are efficient if energy per house is low
    if (numberOfHouses > 0) {
        double houseEfficiency = averageHouseholdEnergy / numberOfHouses;
        return baseScore * (1 - houseEfficiency);
    }
    return baseScore;
}

// IndustrialZone implementation
IndustrialZone::IndustrialZone(const std::string& name, int pop, double energy,
                               int factories, double carbon)
    : CityZone(name, pop, energy), numberOfFactories(factories), carbonEmission(carbon) {}

void IndustrialZone::processEvent(const std::string& event) {
    std::cout << "[INDUSTRIAL] " << zoneName << " processing: " << event;
    if (event == "POWER_FAILURE") {
        std::cout << " - Shutting down " << numberOfFactories << " factories to prevent damage!";
    } else if (event == "NETWORK_OVERLOAD") {
        std::cout << " - Reducing production by 50% to balance grid!";
    }
    std::cout << std::endl;
}

void IndustrialZone::displayStatus() const {
    CityZone::displayStatus();
    std::cout << " | Factories: " << numberOfFactories
              << " | Carbon Emission: " << carbonEmission << " tons/day" << std::endl;
}

double IndustrialZone::getEfficiencyScore() const {
    double baseScore = CityZone::getEfficiencyScore();
    // Industrial zones penalized for high carbon emissions
    return baseScore * (1 - (carbonEmission / 1000.0));
}

// CommercialZone implementation
CommercialZone::CommercialZone(const std::string& name, int pop, double energy,
                               int businesses, double revenue)
    : CityZone(name, pop, energy), numberOfBusinesses(businesses), revenuePerDay(revenue) {}

void CommercialZone::processEvent(const std::string& event) {
    std::cout << "[COMMERCIAL] " << zoneName << " processing: " << event;
    if (event == "NETWORK_OVERLOAD") {
        std::cout << " - Switching to backup communication channels for " << numberOfBusinesses << " businesses!";
    } else if (event == "TRAFFIC_ACCIDENT") {
        std::cout << " - Redirecting deliveries and customers to alternate routes!";
    }
    std::cout << std::endl;
}

void CommercialZone::displayStatus() const {
    CityZone::displayStatus();
    std::cout << " | Businesses: " << numberOfBusinesses
              << " | Revenue: $" << revenuePerDay << "/day" << std::endl;
}

double CommercialZone::getEfficiencyScore() const {
    double baseScore = CityZone::getEfficiencyScore();
    // Commercial zones are efficient if revenue per energy is high
    if (energyConsumption > 0) {
        double revenueEfficiency = revenuePerDay / energyConsumption;
        return baseScore * (1 + revenueEfficiency / 1000);
    }
    return baseScore;
}