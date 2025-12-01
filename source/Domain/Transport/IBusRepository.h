/*****************************************************************//**
 * @file   IBusRepository.h
 * @brief  Interface contract for Bus data access.
 * 
 * @author Fahad Hassan
 * @date   1 12 2025
 *********************************************************************/

#ifndef GUARD_IBUSREPOSITORY_H
#define GUARD_IBUSREPOSITORY_H

#include <string>
#include <Foundation/LinkedList.h>
#include <Domain/Transport/Bus.h>

class IBusRepository
{
public:
    virtual ~IBusRepository() = default;

    /**
     * @brief Retrieves all available buses in the system.
     * @return A linked list containing all Bus objects.
     */
    virtual LinkedList<Bus> LoadAll() = 0;

    /**
     * @brief Finds a specific bus by its ID.
     * @param id The Bus ID to search for (e.g., "B101").
     * @return Pointer to the Bus if found, nullptr otherwise.
     */
    virtual Bus* FindByID(const std::string& id) = 0;
};

#endif // !GUARD_IBUSREPOSITORY_H
