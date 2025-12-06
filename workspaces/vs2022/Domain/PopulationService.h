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
#include <Domain/Person.h>
#include <Domain/CNICHash.h>
#include <Domain/IPersonRepository.h>

class PopulationService
{
private:
    IPersonRepository* m_Repository;
    HashTable<std::string, Person, CNICHash> m_Persons;

public:
    explicit PopulationService(IPersonRepository* repository);

    PopulationService(const PopulationService&) = delete;
    PopulationService& operator=(const PopulationService&) = delete;

    ~PopulationService() = default;

    void Initialize();

    const Person* GetCitizen(const std::string& cnic);
};

#endif // !GUARD_POPULATIONSERVICE_H
