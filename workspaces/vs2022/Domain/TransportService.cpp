/*****************************************************************//**
 * @file   TransportService.cpp
 * @brief  Implementation of the Transport Domain Service.
 *
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#include <stdexcept>
#include <Domain/TransportService.h>
#include <Infrastructure/CTransportRepository.h>

Bus* TransportService::GetBus(const BusID& busID) const
{
    for (Bus& bus : m_Buses)
    {
        if (bus.GetID() == busID)
        {
            return &bus;
        }
    }

    return nullptr;
}

Stop* TransportService::GetStop(const StopID& stopID) const
{
    for (Stop& stop : m_Stops)
    {
        if (stop.getID() == stopID)
        {
            return &stop;
        }
    }

    return nullptr;
}

bool TransportService::Contains(const CompanyID& companyID) const
{
    for (auto& id : m_Companies)
    {
        if (id == companyID)
            return true;
    }
    

    return false;
}

TransportService::TransportService()
{
    m_Repository = new CTransportRepository();

    m_Buses = m_Repository->LoadBusData("data/buses.csv");
    m_Stops = m_Repository->LoadStopData("data/stops.csv");
    m_Companies = m_Repository->LoadCompanyData("data/buses.csv");
}

const LinkedList<std::string>* TransportService::GetBusRoute(const BusID& busID)
{
    Bus* bus = GetBus(busID);

    if (bus == nullptr)
        return nullptr;

    return &bus->GetRoute();
}

const Stack<std::string>* TransportService::GetBusRouteHistory(const BusID& busID)
{
    Bus* bus = GetBus(busID);

    if (bus == nullptr)
        return nullptr;

    return &bus->GetTravelHistory();
}

const LinkedList<CompanyID>* TransportService::GetRegisteredCompanies()
{
    return &m_Companies;
}

bool TransportService::UpdateBusLocation(const BusID& busID, const StopID& stopID)
{
    Bus* bus = GetBus(busID);

    if (bus == nullptr)
        throw std::invalid_argument("Bus: " + busID + " does not exist");

    Stop* stop = GetStop(stopID);

    if (stop == nullptr)
        throw std::runtime_error("Stop: " + stopID + " does not exist");

    bus->MoveTo(stopID);
    return true;
}

bool TransportService::RegisterCompany(const CompanyID& companyID)
{
    if (!Contains(companyID))
    {
        m_Companies.push_back(companyID);
        return true;
    }
    else
    {
        return false;
    }
}

bool TransportService::RegisterBus(const BusID& id, const CompanyID& companyId, const LinkedList<StopID>& route)
{
    if (GetBus(id) != nullptr)
    {
        return false;
    }

    if (route.empty())
    {
        return false;
    }

    for (const auto& stopID : route)
    {
        if (GetStop(stopID) == nullptr)
        {
            return false;
        }
    }

    StopID startLocation = route.front();
    Bus newBus(id, companyId, startLocation);

    LinkedList<StopID> routeCopy = route;
    newBus.SetRoute(std::move(routeCopy));

    m_Buses.push_back(std::move(newBus));

    return true;
}