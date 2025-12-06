/*****************************************************************//**
 * @file   CCsvPersonRepository.h
 * @brief  
 * 
 * @author narut
 * @date   03 12 2025
 *********************************************************************/

#ifndef GUARD_CCSVPERSONREPOSITORY_H
#define GUARD_CCSVPERSONREPOSITORY_H

#include <string>
#include <Domain/IPersonRepository.h>

class CCsvPersonRepository : public IPersonRepository
{
private:
    std::string m_FilePath;

public:
    explicit CCsvPersonRepository(const std::string& filePath);

    ~CCsvPersonRepository() override = default;

    HashTable<CNIC, Person, CNICHash> LoadAll() override;
};

#endif // !GUARD_CCSVPERSONREPOSITORY_H