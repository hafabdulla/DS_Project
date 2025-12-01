/*****************************************************************//**
 * @file   TransportService.cpp
 * @brief  Implementation of the Transport Domain Service.
 *
 * @author Fahad Hassan
 * @date   1 12 2025
 *********************************************************************/

#include <Domain/Transport/TransportService.h>

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
    for (const auto& bus : m_Buses)
    {
        if (bus.GetBusID() == busID)
        {
            return &bus.GetRoute();
        }
    }

    return nullptr;
}