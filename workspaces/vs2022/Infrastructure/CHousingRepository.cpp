#include <Infrastructure/CHousingRepository.h>
#include <fstream>
#include <sstream>
#include <iostream>

HashTable<CNIC, Person, CNICHash> CHousingRepository::LoadPersonData(const std::string& filePath)
{
    HashTable<CNIC, Person, CNICHash> persons(1009);

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::invalid_argument("Failed to open file: " + filePath);
        return persons;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string segment;

        std::string cnic, name, ageStr, sector, street, houseNo, occupation;

        std::getline(ss, cnic, ',');
        std::getline(ss, name, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, sector, ',');
        std::getline(ss, street, ',');
        std::getline(ss, houseNo, ',');
        std::getline(ss, occupation, ',');

        if (!occupation.empty() && occupation.back() == '\r')
            occupation.pop_back();

        int age = 0;
        try {
            age = std::stoi(ageStr);
        }
        catch (...) {
            age = 0;
        }

        std::string fullAddress = "House " + houseNo + ", Street " + street + ", " + sector;

        Person newPerson(cnic, name, age, fullAddress, occupation);

        persons.insert(cnic, newPerson);
    }

    return persons;
}

Tree<std::string, std::string> CHousingRepository::LoadHousingData(const std::string& filePath)
{
    Tree<std::string, std::string> housingTree;
    std::string rootKey = "Islamabad";
    housingTree.AddRoot(rootKey, rootKey);

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::invalid_argument("Failed to open file: " + filePath);
        return housingTree;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string segment;
        std::string cnic, name, ageStr, sector, street, houseNo, occupation;

        std::getline(ss, cnic, ',');
        std::getline(ss, name, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, sector, ',');
        std::getline(ss, street, ',');
        std::getline(ss, houseNo, ',');
        std::getline(ss, occupation, ',');

        // Clean up trailing carriage returns
        if (!houseNo.empty() && houseNo.back() == '\r') houseNo.pop_back();

        std::string& sectorKey = sector;
        std::string streetKey = sector + ":" + street;
        std::string houseKey = streetKey + ":" + houseNo;

        // Check if sector exists to avoid duplicates
        if (!housingTree.Contains(sectorKey))
        {
            housingTree.AddChild(rootKey, sectorKey, sectorKey);
        }

        // Check streetKey to ensure we don't add "Street 22" twice to "G-10"
        if (!housingTree.Contains(streetKey))
        {
            housingTree.AddChild(sectorKey, streetKey, streetKey);
        }

        if (!housingTree.Contains(houseNo))
        {
            housingTree.AddChild(streetKey, houseKey, houseKey);
        }
    }

    return housingTree;
}