#include <Domain/Population/PopulationService.h>

PopulationService::PopulationService(IPersonRepository* repository)
    : m_Repository(repository)
{
}

void PopulationService::Initialize()
{
    if (m_Repository)
    {
        m_Persons = m_Repository->LoadAll();
    }
}

const Person* PopulationService::GetCitizen(const std::string& cnic)
{
    for (const auto& record : m_Persons)
    {
        if (record.key == cnic)
        {
            return &record.value;
        }
    }
}