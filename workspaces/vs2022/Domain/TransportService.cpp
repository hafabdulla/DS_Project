/*****************************************************************//**
 * @file   TransportService.cpp
 * @brief  Implementation of the Transport Domain Service.
 *
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#include <stdexcept>
#include <Domain/TransportService.h>
#include <Infrastructure/CCsvBusRepository.h>

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

TransportService::TransportService()
{
    m_Repository = new CCsvBusRepository("data/buses.csv");

    if (m_Repository)
    {
        m_Buses = m_Repository->LoadAll();
    }
    else
    {
        throw std::runtime_error("Failed to load Bus Repository");
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
