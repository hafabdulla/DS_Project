#include <Infrastructure/CCsvPersonRepository.h>
#include <fstream>
#include <sstream>
#include <iostream>

CCsvPersonRepository::CCsvPersonRepository(const std::string& filePath)
    : m_FilePath(filePath)
{
}

HashTable<CNIC, Person, CNICHash> CCsvPersonRepository::LoadAll()
{
    HashTable<CNIC, Person, CNICHash> persons(1009);

    std::ifstream file(m_FilePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << m_FilePath << std::endl;
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
