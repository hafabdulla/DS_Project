/*****************************************************************//**
 * @file   IPersonRepository.h
 * @brief  
 * 
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#ifndef GUARD_IPERSONREPOSITORY_H
#define GUARD_IPERSONREPOSITORY_H

#include <Foundation/HashTable.h>
#include <Domain/Population/CNICHash.h>
#include <Domain/Population/Person.h>

class IPersonRepository
{
public:
    virtual ~IPersonRepository() = default;

    virtual HashTable<CNIC, Person, CNICHash> LoadAll() = 0;
};

#endif // !GUARD_IPERSONREPOSITORY_H
