#include "Company.h"

Company::Company(const CompanyID& id, const std::string& name, const std::string& info)
    : m_ID(id), m_Name(name), m_Info(info)
{
}

const CompanyID& Company::GetID() const noexcept
{
    return m_ID;
}

const std::string& Company::GetName() const noexcept
{
    return m_Name;
}

const std::string& Company::GetInfo() const noexcept
{
    return m_Info;
}

