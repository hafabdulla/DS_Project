/*****************************************************************//**
 * @file   IPersonRepository.h
 * @brief  
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_IHOUSINGREPOSITORY_H
#define GUARD_IHOUSINGREPOSITORY_H

#include <Foundation/HashTable.h>
#include <Foundation/Tree.h>
#include <Domain/CNICHash.h>
#include <Domain/Person.h>

class IHousingRepository
{
public:
    virtual ~IHousingRepository() = default;

    virtual HashTable<CNIC, Person, CNICHash> LoadPersonData(const std::string& filePath) = 0;
    virtual Tree<std::string, std::string> LoadHousingData(const std::string& filePath) = 0;
};

#endif // !GUARD_IHOUSINGREPOSITORY_H
