/*****************************************************************//**
 * @file   IBusRepository.h
 * @brief  Interface contract for Bus data access.
 * 
 * @author Fahad Hassan
 * @date   01 12 2025
 *********************************************************************/

#ifndef GUARD_IBUSREPOSITORY_H
#define GUARD_IBUSREPOSITORY_H

#include <string>
#include <Foundation/LinkedList.h>
#include <Domain/Bus.h>

class IBusRepository
{
public:
    virtual ~IBusRepository() = default;

    virtual LinkedList<Bus> LoadAll() = 0;
};

#endif // !GUARD_IBUSREPOSITORY_H
