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
#include <Domain/StringHash.h>

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
    void GetAgeDistribution(int& outChildren, int& outYoung, int& outAdults, int& outSeniors);

    bool RegisterSector(const std::string& sectorName);
    bool RegisterStreet(const std::string& sectorName, const std::string& streetName);
    bool RegisterHouse(const std::string& sectorName, const std::string& streetName, const std::string& houseNo);
    bool RegisterFamily(const std::string& sectorName, const std::string& streetName, const std::string& houseNo,
        const std::string& familyName);
    bool RegisterIndividual(const std::string& sectorName, const std::string& streetName, const std::string& houseNo,
        const std::string& familyName, const Person& person);

    template<typename Func>
    void TraverseHousingHierarchy(Func visit) const;

    template<typename Func>
    void TraverseOccupationSummary(Func visit);
};

#endif // !GUARD_POPULATIONSERVICE_H

template<typename Func>
inline void PopulationService::TraverseHousingHierarchy(Func visit) const
{
    m_HousingData.PreOrderTraversal(visit);
}

template<typename Func>
inline void PopulationService::TraverseOccupationSummary(Func visit)
{
    HashTable<std::string, int, StringHash> jobCounts(50);

    for (auto& entry : m_Persons)
    {
        const std::string& job = entry.value.GetOccupation();

        if (jobCounts.contains(job))
        {
            jobCounts[job]++;
        }
        else
        {
            jobCounts.insert(job, 1);
        }
    }

    for (auto& entry : jobCounts)
    {
        visit(entry.key, entry.value);
    }
}