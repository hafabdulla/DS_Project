/*****************************************************************//**
 * @file   Stop.h
 * @brief  Represents a bus stop.
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_STOP_H
#define GUARD_STOP_H

#include <string>
#include <Domain/Coordinate.h>

typedef std::string StopID;

class Stop
{
private:
    StopID m_ID;
    std::string m_Name;
    Coordinate m_Coordinate;

public:
    Stop(const StopID& stopID, const std::string& name, const Coordinate& coordinates)
        : m_ID(stopID), m_Name(name), m_Coordinate(coordinates)
    {
    }

    const std::string getID() const
    {
        return m_ID;
    }

    const std::string getName() const
    {
        return m_Name;
    }

    const Coordinate getCoordinate() const
    {
        return m_Coordinate;
    }
};

#endif // !GUARD_STOP_H