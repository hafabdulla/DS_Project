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

Stop* TransportService::GetStop(const StopID& stopID)
{
    if (m_Network.HasVertex(stopID))
    {
        return m_Network.GetVertex(stopID);
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
    LinkedList<Stop> stops = m_Repository->LoadStopData("data/stops.csv");
    m_Companies = m_Repository->LoadCompanyData("data/buses.csv");

    for (const auto& stop : stops)
    {
        m_Network.AddVertex(stop.getID(), stop);
    }

    for (const auto& bus : m_Buses)
    {
        const LinkedList<StopID>& route = bus.GetRoute();

        if (route.empty()) 
            continue;

        auto it = route.begin();
        auto nextIt = route.begin();
        ++nextIt;

        while (nextIt != route.end())
        {
            StopID src = *it;
            StopID dest = *nextIt;

            if (m_Network.HasVertex(src) && m_Network.HasVertex(dest))
            {
                Stop* s1 = m_Network.GetVertex(src);
                Stop* s2 = m_Network.GetVertex(dest);
                double dist = s1->getCoordinate().DistanceTo(s2->getCoordinate());

                m_Network.AddEdge(src, dest, dist);
            }

            ++it;
            ++nextIt;
        }
    }
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
        throw std::invalid_argument("Bus not found");

    if (!m_Network.HasVertex(stopID))
        throw std::runtime_error("Stop not found");

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

bool TransportService::RegisterStop(const StopID& stopID, const std::string& name, double lat, double lon)
{
    if (m_Network.HasVertex(stopID))
    {
        return false;
    }

    Coordinate coord(lat, lon);
    Stop newStop(stopID, name, coord);

    m_Network.AddVertex(stopID, newStop);
    return true;
}

bool TransportService::AddRoad(const StopID& sourceID, const StopID& destID)
{
    if (m_Network.HasVertex(sourceID) && m_Network.HasVertex(destID))
    {
        Stop* s1 = m_Network.GetVertex(sourceID);
        Stop* s2 = m_Network.GetVertex(destID);
        double dist = s1->getCoordinate().DistanceTo(s2->getCoordinate());

        m_Network.AddEdge(sourceID, destID, dist);
        return true;
    }

    return false;
}

LinkedList<std::string> TransportService::FindShortestPath(const StopID& start, const StopID& end, double& outDistance)
{
    return m_Network.GetShortestPath(start, end, outDistance);
}
