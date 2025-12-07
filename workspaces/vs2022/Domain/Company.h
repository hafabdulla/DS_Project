/*****************************************************************//**
 * @file   Company.h
 * @brief  
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_COMPANY_H
#define GUARD_COMPANY_H

#include <string>

typedef std::string CompanyID;

class Company
{
private:
    CompanyID m_ID;
    std::string m_Name;
    std::string m_Info;

public:
    Company() = default;
    Company(const CompanyID& id, const std::string& name, const std::string& info);

    const CompanyID& GetID() const noexcept;
    const std::string& GetName() const noexcept;
    const std::string& GetInfo() const noexcept;
};

#endif // !GUARD_COMPANY_H
