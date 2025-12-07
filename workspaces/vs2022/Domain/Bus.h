/*****************************************************************//**
 * @file   Bus.h
 * @brief  Represents a bus
 * 
 * @author Fahad Hassan
 * @date   01 12 2025
 *********************************************************************/

#ifndef GUARD_BUS_H
#define GUARD_BUS_H

#include <string>
#include <Foundation/LinkedList.h>
#include <Foundation/Stack.h>
#include <Domain/Stop.h>
#include <Domain/Company.h>

typedef std::string BusID;

class Bus
{
private:
    BusID m_BusID;
    CompanyID m_CompanyID;
    StopID m_CurrentStopID;
    LinkedList<StopID> m_Route;
    Stack<StopID> m_TravelHistory;

public:
    Bus() = default;
    Bus(const BusID& id, const CompanyID& companyID, const StopID& currentStopID);

    const BusID& GetID() const noexcept;
    const CompanyID& GetCompanyID() const noexcept;
    const StopID& GetCurrentStopID() const noexcept;
    const LinkedList<StopID>& GetRoute() const noexcept;
    const Stack<StopID>& GetTravelHistory() const noexcept;

    void SetRoute(LinkedList<StopID>&& route);
    void AddStop(const StopID& stopID);
    void SetCurrentLocation(const StopID& stopID);
    void MoveTo(const StopID& stopID);
};

#endif // !GUARD_BUS_H
