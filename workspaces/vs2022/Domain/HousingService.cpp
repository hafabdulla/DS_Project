#include <Domain/HousingService.h>
#include <Infrastructure/CHousingRepository.h>

HousingService::HousingService()
{
    m_Repository = new CHousingRepository();
    m_Persons = m_Repository->LoadPersonData("data/population.csv");
    m_HousingData = m_Repository->LoadHousingData("data/population.csv");
}

const Person* HousingService::GetCitizen(const std::string& cnic)
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

void HousingService::GetAgeDistribution(int& outChildren, int& outYoung, int& outAdults, int& outSeniors)
{
    outChildren = 0; // 0-18
    outYoung = 0;    // 19-35
    outAdults = 0;   // 36-60
    outSeniors = 0;  // 60+

    for (const auto& entry : m_Persons)
    {
        int age = entry.value.GetAge();

        if (age <= 18)
            outChildren++;
        else if (age <= 35)
            outYoung++;
        else if (age <= 60)
            outAdults++;
        else
            outSeniors++;
    }
}

void HousingService::GetResidentsInSector(const std::string& sectorName, LinkedList<const Person*>& outResidents)
{
    outResidents.clear();

    auto visitor = [&](const std::string& key, const std::string& val)
        {
            size_t lastColon = key.find_last_of(':');
            std::string potentialCNIC = (lastColon != std::string::npos) ? key.substr(lastColon + 1) : key;

            if (m_Persons.contains(potentialCNIC))
            {
                //outResidents.push_back(m_Persons.Get(potentialCNIC));
                outResidents.push_back(&m_Persons.at(potentialCNIC));
            }   
        };

    m_HousingData.TraverseSubtree(sectorName, visitor);
}

bool HousingService::RegisterSector(const std::string& sectorName)
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

bool HousingService::RegisterStreet(const std::string& sectorName, const std::string& streetName)
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

bool HousingService::RegisterHouse(const std::string& sectorName, const std::string& streetName, const std::string& houseNo)
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

bool HousingService::RegisterFamily(const std::string& sectorName, const std::string& streetName, const std::string& houseNo,
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

bool HousingService::RegisterIndividual(const std::string& sectorName, const std::string& streetName, const std::string& houseNo, const std::string& familyName, const Person& person)
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