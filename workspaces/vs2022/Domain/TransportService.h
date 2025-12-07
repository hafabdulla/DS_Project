/*****************************************************************//**
 * @file   TransportService.h
 * @brief  Domain service for managing transport operations.
 * 
 * @author Fahad Hassan
 * @date   1 12 2025
 *********************************************************************/

#ifndef GUARD_TRANSPORTSERVICE_H
#define GUARD_TRANSPORTSERVICE_H

#include <string>
#include <Foundation/LinkedList.h>
#include <Foundation/Stack.h>
#include <Domain/Bus.h>
#include <Domain/IBusRepository.h>

class TransportService
{
private:
    IBusRepository* m_Repository;
    LinkedList<Bus> m_Buses;

    Bus* GetBus(std::string busID) const;

public:
    explicit TransportService();

    TransportService(const TransportService&) = delete;
    TransportService& operator=(const TransportService&) = delete;

    ~TransportService() = default;

    const LinkedList<std::string>* GetBusRoute(const std::string& busID);
    const Stack<std::string>* GetBusRouteHistory(const std::string& busID);

    bool UpdateBusLocation(const std::string& busID, const std::string& newStop);
};

#endif // !GUARD_TRANSPORTSERVICE_H
