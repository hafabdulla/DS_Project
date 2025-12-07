#include <Domain/PopulationService.h>
#include <Infrastructure/CHousingRepository.h>

PopulationService::PopulationService()
{
    m_Repository = new CHousingRepository();
    m_Persons = m_Repository->LoadPersonData("data/population.csv");
    m_HousingData = m_Repository->LoadHousingData("data/population.csv");
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

    return nullptr;
}

bool PopulationService::RegisterSector(const std::string& sectorName)
{
    std::string rootKey = "Islamabad";

    if (m_HousingData.Contains(sectorName) == false)
    {
        m_HousingData.AddChild(rootKey, sectorName, sectorName);
        return true;
    }
    else
        return false;
}

bool PopulationService::RegisterStreet(const std::string& sectorName, const std::string& streetName)
{
    if (m_HousingData.Contains(sectorName) == false)
    {
        return false;
    }

    std::string streetKey = sectorName + ":" + streetName;

    if (m_HousingData.Contains(streetKey) == false)
    {
        m_HousingData.AddChild(sectorName, streetKey, streetKey);
        return true;
    }
    else
        return false;
}

bool PopulationService::RegisterHouse(const std::string& sectorName, const std::string& streetName, const std::string& houseNo)
{
    std::string streetKey = sectorName + ":" + streetName;
    std::string houseKey = streetKey + ":" + houseNo;

    if (!m_HousingData.Contains(streetKey))
        throw std::invalid_argument("Error: Street " + streetName + " in " + sectorName + " does not exist.");

    if (!m_HousingData.Contains(houseKey))
    {
        m_HousingData.AddChild(streetKey, houseKey, houseKey);
        return true;
    }
    else
        return false;
}

bool PopulationService::RegisterFamily(const std::string& sectorName, const std::string& streetName, const std::string& houseNo,
    const std::string& familyName)
{
    std::string houseKey = sectorName + ":" + streetName + ":" + houseNo;

    std::string familyKey = houseKey + ":" + familyName;

    if (!m_HousingData.Contains(houseKey))
    {
        return false;
    }

    if (m_HousingData.Contains(familyKey))
    {
        return false;
    }

    m_HousingData.AddChild(houseKey, familyKey, familyName);
    return true;
}

bool PopulationService::RegisterIndividual(const std::string& sectorName, const std::string& streetName, const std::string& houseNo, const std::string& familyName, const Person& person)
{
    std::string familyKey = sectorName + ":" + streetName + ":" + houseNo + ":" + familyName;

    if (!m_HousingData.Contains(familyKey))
    {
        return false;
    }

    if (m_Persons.contains(person.GetCNIC()))
    {
        return false;
    }

    std::string individualTreeKey = familyKey + ":" + person.GetCNIC();
    m_HousingData.AddChild(familyKey, individualTreeKey, person.GetName());
    m_Persons.insert(person.GetCNIC(), person);

    return true;
}