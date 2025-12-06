/*****************************************************************//**
 * @file   Person.h
 * @brief  
 * 
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#ifndef GUARD_PERSON_H
#define GUARD_PERSON_H

#include <string>

typedef std::string CNIC;

class Person
{
private:
    CNIC m_CNIC;
    std::string m_Name;
    int m_Age;
    std::string m_Address;
    std::string m_Occupation;

public:
    Person() = default;
    Person(const CNIC& cnic, const std::string name, int age, const std::string& address, const std::string& occupation);

    CNIC GetCNIC() const noexcept;
    const std::string GetName() const noexcept;
    const int GetAge() const noexcept;
    const std::string GetAddress() const noexcept;
    const std::string GetOccupation() const noexcept;

    void SetAge(int age);
    void SetAddress(const std::string& address);
    void SetOccupation(const std::string& occupation);
};

#endif // !GUARD_PERSON_H
