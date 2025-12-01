/*****************************************************************//**
 * @file   CsvBusRepository.cpp
 * @brief  Implementation of CSV parsing logic.
 *
 * @author Fahad Hassan
 * @date   27 11 2025
 *********************************************************************/

#include <Infrastructure/CCsvBusRepository.h>
#include <fstream>
#include <sstream>
#include <iostream>

CsvBusRepository::CsvBusRepository(const std::string& filePath)
    : m_FilePath(filePath)
{
}

LinkedList<Bus> CsvBusRepository::LoadAll()
{
    LinkedList<Bus> buses;
    std::ifstream file(m_FilePath);

    if (!file.is_open())
    {
        std::cerr << "[Error] Failed to open file: " << m_FilePath << std::endl;
        return buses;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) 
            continue;

        std::stringstream ss(line);
        std::string segment;
        std::string id, company, currentStop, routeStr;

        if (!std::getline(ss, id, ',')) 
            continue;

        if (!std::getline(ss, company, ',')) 
            continue;

        if (!std::getline(ss, currentStop, ',')) 
            continue;

        std::getline(ss, routeStr);

        Bus newBus(id, company, currentStop);
        ParseRoute(newBus, routeStr);

        buses.push_back(std::move(newBus));
    }

    return buses;
}

Bus* CsvBusRepository::FindByID(const std::string& id)
{
    return nullptr;
}

void CsvBusRepository::ParseRoute(Bus& bus, const std::string& routeStr) const
{
    std::string temp = routeStr;
    std::string delimiter = " > ";
    size_t pos = 0;

    if (!temp.empty() && temp.front() == '"') temp.erase(0, 1);
    if (!temp.empty() && temp.back() == '"') temp.pop_back();

    while ((pos = temp.find(delimiter)) != std::string::npos)
    {
        std::string token = temp.substr(0, pos);
        bus.AddStop(token);
        temp.erase(0, pos + delimiter.length());
    }
    if (!temp.empty())
    {
        if (temp.back() == '\r') temp.pop_back();
        bus.AddStop(temp);
    }
}