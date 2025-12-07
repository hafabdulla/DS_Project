#include <Domain/Bus.h>

Bus::Bus(const std::string& id, const std::string& company, const std::string& currentLocation)
    : m_BusID(id), m_Company(company), m_CurrentLocation(currentLocation)
{
    m_TravelHistory.push(currentLocation);
}

const std::string& Bus::GetBusID() const noexcept
{
    return m_BusID;
}

const std::string& Bus::GetCompany() const noexcept
{
    return m_Company;
}

const std::string& Bus::GetCurrentLocation() const noexcept
{
    return m_CurrentLocation;
}

const Stack<std::string>& Bus::GetTravelHistory() const noexcept
{
    return m_TravelHistory;
}

const LinkedList<std::string>& Bus::GetRoute() const noexcept
{
    return m_Route;
}

void Bus::SetRoute(LinkedList<std::string>&& route)
{
    m_Route = std::move(route);
}

void Bus::AddStop(const std::string& stopName)
{
    m_Route.push_back(stopName);
}

void Bus::SetCurrentLocation(const std::string& location)
{
    m_CurrentLocation = location;
}

void Bus::MoveTo(const std::string& stopName)
{
    m_TravelHistory.push(stopName);
    m_CurrentLocation = stopName;
}