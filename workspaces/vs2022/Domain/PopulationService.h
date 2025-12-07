/*****************************************************************//**
 * @file   PopulationService.h
 * @brief  Domain service for managing population operations.
 * 
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#ifndef GUARD_POPULATIONSERVICE_H
#define GUARD_POPULATIONSERVICE_H

#include <string>
#include <Foundation/HashTable.h>
#include <Foundation/Tree.h>
#include <Domain/Person.h>
#include <Domain/CNICHash.h>
#include <Domain/IHousingRepository.h>

class PopulationService
{
private:
    IHousingRepository* m_Repository;
    HashTable<std::string, Person, CNICHash> m_Persons;
    Tree<std::string, std::string> m_HousingData;

public:
    explicit PopulationService();

    PopulationService(const PopulationService&) = delete;
    PopulationService& operator=(const PopulationService&) = delete;

    ~PopulationService() = default;

    const Person* GetCitizen(const std::string& cnic);
    bool RegisterSector(const std::string& sectorName);
    bool RegisterStreet(const std::string& sectorName, const std::string& streetName);
    bool RegisterHouse(const std::string& sectorName, const std::string& streetName, const std::string& houseNo);
};

#endif // !GUARD_POPULATIONSERVICE_H
