/*****************************************************************//**
 * @file   Bus.h
 * @brief  Represents a bus
 * 
 * @author Fahad Hassan
 * @date   01 12 2025
 *********************************************************************/

#ifndef GUARD_BUS_H
#define GUARD_BUS_H

#include <string>
#include <Foundation/LinkedList.h>

class Bus
{
private:
    std::string m_BusID;
    std::string m_Company;
    std::string m_CurrentLocation;
    LinkedList<std::string> m_Route;

public:
    Bus() = default;
    Bus(const std::string& id, const std::string& company, const std::string& currentLocation);

    const std::string& GetBusID() const noexcept;
    const std::string& GetCompany() const noexcept;
    const std::string& GetCurrentLocation() const noexcept;
    const LinkedList<std::string>& GetRoute() const noexcept;

    void SetRoute(LinkedList<std::string>&& route);
    void AddStop(const std::string& stopName);
    void SetCurrentLocation(const std::string& location);
};

inline Bus::Bus(const std::string& id, const std::string& company, const std::string& currentLocation)
    : m_BusID(id), m_Company(company), m_CurrentLocation(currentLocation)
{
}

inline const std::string& Bus::GetBusID() const noexcept
{
    return m_BusID;
}

inline const std::string& Bus::GetCompany() const noexcept
{
    return m_Company;
}

inline const std::string& Bus::GetCurrentLocation() const noexcept
{
    return m_CurrentLocation;
}

inline const LinkedList<std::string>& Bus::GetRoute() const noexcept
{
    return m_Route;
}

inline void Bus::SetRoute(LinkedList<std::string>&& route)
{
    m_Route = std::move(route);
}

inline void Bus::AddStop(const std::string& stopName)
{
    m_Route.push_back(stopName);
}

inline void Bus::SetCurrentLocation(const std::string& location)
{
    m_CurrentLocation = location;
}

#endif // !GUARD_BUS_H
