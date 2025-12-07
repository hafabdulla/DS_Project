#include <Infrastructure/CTransportRepository.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

void CTransportRepository::parseRoute(Bus& bus, const std::string& routeString)
{
    std::string temp = routeString;
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

LinkedList<Stop> CTransportRepository::LoadStopData(const std::string& filePath)
{
    LinkedList<Stop> stops;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::string line;

    // Skip the header line
    if (!std::getline(file, line))
    {
        return stops;
    }

    while (std::getline(file, line))
    {
        if (line.empty() || line == "\r")
            continue;

        std::stringstream ss(line);
        std::string id;
        std::string name;
        std::string coordStr;

        if (!std::getline(ss, id, ','))
            continue;

        if (!std::getline(ss, name, ','))
            continue;

        if (std::getline(ss, coordStr))
        {
            if (!coordStr.empty() && coordStr.back() == '\r')
                coordStr.pop_back();

            if (coordStr.size() >= 2 && coordStr.front() == '"' && coordStr.back() == '"')
            {
                coordStr = coordStr.substr(1, coordStr.size() - 2);
            }

            size_t commaPos = coordStr.find(',');
            if (commaPos != std::string::npos)
            {
                try
                {
                    std::string latStr = coordStr.substr(0, commaPos);
                    std::string lonStr = coordStr.substr(commaPos + 1);

                    float lat = std::stof(latStr);
                    float lon = std::stof(lonStr);

                    Coordinate coord(lat, lon);
                    Stop newStop(id, name, coord);
                    stops.push_back(newStop);
                }
                catch (const std::exception& e)
                {
                    throw std::runtime_error("Failed to parse coordinates for stop " + id + ": " + e.what());
                }
            }
        }
    }

    return stops;
}

LinkedList<Bus> CTransportRepository::LoadBusData(const std::string& filePath)
{
    LinkedList<Bus> buses;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
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
        parseRoute(newBus, routeStr);

        buses.push_back(std::move(newBus));
    }

    return buses;
}

LinkedList<CompanyID> CTransportRepository::LoadCompanyData(const std::string& filePath)
{
    LinkedList<CompanyID> companies;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::string line;

    if (!std::getline(file, line))
    {
        return companies;
    }

    while (std::getline(file, line))
    {
        if (line.empty() || line == "\r")
            continue;

        std::stringstream ss(line);
        std::string busNo;
        std::string companyName;

        if (!std::getline(ss, busNo, ','))
            continue;

        if (!std::getline(ss, companyName, ','))
            continue;

        if (!companyName.empty() && companyName.back() == '\r')
            companyName.pop_back();

        bool exists = false;
        for (const auto& existingCompany : companies)
        {
            if (existingCompany == companyName)
            {
                exists = true;
                break;
            }
        }

        if (!exists && !companyName.empty())
        {
            companies.push_back(companyName);
        }
    }

    return companies;
}