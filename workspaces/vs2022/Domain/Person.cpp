#include <Domain/Person.h>

Person::Person(const CNIC& cnic, const std::string name, int age, const std::string& address, const std::string& occupation)
    : m_CNIC(cnic), m_Name(name), m_Age(age), m_Address(address), m_Occupation(occupation)
{
}

CNIC Person::GetCNIC() const noexcept
{
    return m_CNIC;
}

const std::string Person::GetName() const noexcept
{
    return m_Name;
}

const int Person::GetAge() const noexcept
{
    return m_Age;
}

const std::string Person::GetAddress() const noexcept
{
    return m_Address;
}

const std::string Person::GetOccupation() const noexcept
{
    return m_Occupation;
}

void Person::SetAge(int age)
{
    m_Age = age;
}

void Person::SetAddress(const std::string& address)
{
    m_Address = address;
}

void Person::SetOccupation(const std::string& occupation)
{
    m_Occupation = occupation;
}
