/*****************************************************************//**
 * @file   ITransportRepository.h
 * @brief  Interface for all the repository needs of the transport 
 *         module.
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_ITRANSPORTREPOSITORY_H
#define GUARD_ITRANSPORTREPOSITORY_H

#include <Foundation/LinkedList.h>
#include <Domain/Stop.h>
#include <Domain/Bus.h>

class ITransportRepository
{
public:
    ~ITransportRepository() = default;

    virtual LinkedList<Stop> LoadStopData(const std::string& filePath) = 0;
    virtual LinkedList<Bus> LoadBusData(const std::string& filePath) = 0;
};

#endif // !GUARD_ITRANSPORTREPOSITORY_H
