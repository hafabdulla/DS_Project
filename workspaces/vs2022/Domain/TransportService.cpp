/*****************************************************************//**
 * @file   TransportService.cpp
 * @brief  Implementation of the Transport Domain Service.
 *
 * @author Fahad Hassan
 * @date   1 12 2025
 *********************************************************************/

#include <Domain/TransportService.h>

Bus* TransportService::GetBus(std::string busID) const
{
    for (Bus& bus : m_Buses)
    {
        if (bus.GetBusID() == busID)
        {
            return &bus;
        }
    }

    return nullptr;
}

TransportService::TransportService(IBusRepository* repository)
    : m_Repository(repository)
{
}

void TransportService::Initialize()
{
    if (m_Repository)
    {
        m_Buses = m_Repository->LoadAll();
    }
}

const LinkedList<std::string>* TransportService::GetBusRoute(const std::string& busID)
{
    Bus* bus = GetBus(busID);

    if (bus == nullptr)
        return nullptr;

    return &bus->GetRoute();
}

const Stack<std::string>* TransportService::GetBusRouteHistory(const std::string& busID)
{
    Bus* bus = GetBus(busID);

    if (bus == nullptr)
        return nullptr;

    return &bus->GetTravelHistory();
}

bool TransportService::UpdateBusLocation(const std::string& busID, const std::string& newStop)
{
    Bus* bus = GetBus(busID);

    if (bus == nullptr)
        return false;

    bus->MoveTo(newStop);
    return true;
}
