/*****************************************************************//**
 * @file   CHousingRepository.h
 * @brief  
 * 
 * @author narut
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_CCSVPERSONREPOSITORY_H
#define GUARD_CCSVPERSONREPOSITORY_H

#include <string>
#include <Domain/IHousingRepository.h>

class CHousingRepository : public IHousingRepository
{
public:
    ~CHousingRepository() override = default;

    HashTable<CNIC, Person, CNICHash> LoadPersonData(const std::string& filePath) override;
    Tree<std::string, std::string> LoadHousingData(const std::string& filePath) override;
};

#endif // !GUARD_CCSVPERSONREPOSITORY_H