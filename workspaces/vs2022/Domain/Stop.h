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
    const StopID m_ID;
    const std::string m_Name;
    const Coordinate m_Coordinate;

public:
    Stop(std::string stopID, std::string name, Coordinate coordinates)
        : m_ID(stopID), m_Name(name), m_Coordinate(coordinates)
    {
    }

    const std::string getID()
    {
        return m_ID;
    }

    const std::string getName()
    {
        return m_Name;
    }

    const Coordinate getCoordinate()
    {
        return m_Coordinate;
    }
};

#endif // !GUARD_STOP_H