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
#include <Domain/Bus.h>
#include <Domain/IBusRepository.h>

class TransportService
{
private:
    IBusRepository* m_Repository;
    LinkedList<Bus> m_Buses;

public:
    explicit TransportService(IBusRepository* repository);

    TransportService(const TransportService&) = delete;
    TransportService& operator=(const TransportService&) = delete;

    ~TransportService() = default;

    void Initialize();

    const LinkedList<std::string>* GetBusRoute(const std::string& busID);
};

#endif // !GUARD_TRANSPORTSERVICE_H
