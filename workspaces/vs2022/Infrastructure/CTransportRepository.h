/*****************************************************************//**
 * @file   CTransportRepository.h
 * @brief  Implementation of the ITransportRepository
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_CTRANSPORTREPOSITORY_H
#define GUARD_CTRANSPORTREPOSITORY_H

#include <string>
#include <Domain/ITransportRepository.h>

class CTransportRepository : public ITransportRepository
{
private:
    void parseRoute(Bus& bus, const std::string& routeString);
    
public:

    LinkedList<Stop> LoadStopData(const std::string& filePath) override;
    LinkedList<Bus> LoadBusData(const std::string& filePath) override;
};

#endif // !GUARD_CTRANSPORTREPOSITORY_H
