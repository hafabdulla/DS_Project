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

#endif // !GUARD_BUS_H
