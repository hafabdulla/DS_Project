#include <Domain/Bus.h>

Bus::Bus(const BusID& id, const CompanyID& companyID, const StopID& currentStopID)
    : m_BusID(id), m_CompanyID(companyID), m_CurrentStopID(currentStopID)
{
    m_TravelHistory.push(currentStopID);
}

const std::string& Bus::GetID() const noexcept
{
    return m_BusID;
}

const std::string& Bus::GetCompanyID() const noexcept
{
    return m_CompanyID;
}

const std::string& Bus::GetCurrentStopID() const noexcept
{
    return m_CurrentStopID;
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

void Bus::AddStop(const StopID& stopID)
{
    m_Route.push_back(stopID);
}

void Bus::SetCurrentLocation(const StopID& stopID)
{
    m_CurrentStopID = stopID;
}

void Bus::MoveTo(const StopID& stopID)
{
    m_TravelHistory.push(stopID);
    m_CurrentStopID = stopID;
}