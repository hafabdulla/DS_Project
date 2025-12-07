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
#include <Foundation/Graph.h>
#include <Foundation/LinkedList.h>
#include <Foundation/Stack.h>
#include <Domain/Bus.h>
#include <Domain/ITransportRepository.h>

struct StringHash 
{
    std::size_t operator()(const std::string& key) const 
    {
        std::size_t hash = 67; // six-seven!!!

        for (char c : key) 
        {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }
};

class TransportService
{
private:
    ITransportRepository* m_Repository;
    LinkedList<Bus> m_Buses;
    Graph<StopID, Stop, StringHash> m_Network;
    LinkedList<CompanyID> m_Companies;

    Bus* GetBus(const BusID& busID) const;
    Stop* GetStop(const StopID& stopID);
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
    bool RegisterStop(const StopID& stopID, const std::string& name, double lat, double lon);
    bool AddRoad(const StopID& sourceID, const StopID& destID);
    LinkedList<std::string> FindShortestPath(const StopID& start, const StopID& end, double& outDistance);
    bool FindNearestBus(double userLat, double userLon, std::string& outBusID, double& outDistance);
};

#endif // !GUARD_TRANSPORTSERVICE_H
