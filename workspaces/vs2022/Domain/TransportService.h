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
#include <Domain/ITransportRepository.h>

class TransportService
{
private:
    ITransportRepository* m_Repository;
    LinkedList<Bus> m_Buses;
    LinkedList<Stop> m_Stops;
    LinkedList<CompanyID> m_Companies;

    Bus* GetBus(const BusID& busID) const;
    Stop* GetStop(const StopID& stopID) const;
    bool Contains(const CompanyID& companyID) const;

public:
    explicit TransportService();

    TransportService(const TransportService&) = delete;
    TransportService& operator=(const TransportService&) = delete;

    ~TransportService() = default;

    const LinkedList<std::string>* GetBusRoute(const BusID& busID);
    const Stack<std::string>* GetBusRouteHistory(const BusID& busID);
    const LinkedList<CompanyID>* GetRegisteredCompanies();

    bool UpdateBusLocation(const BusID& busID, const StopID& stopID);
    bool RegisterCompany(const CompanyID& companyID);
    bool RegisterBus(const BusID& id, const CompanyID& companyId, const LinkedList<StopID>& route);
};

#endif // !GUARD_TRANSPORTSERVICE_H
