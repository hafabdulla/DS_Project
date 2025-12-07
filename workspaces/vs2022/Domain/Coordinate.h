/*****************************************************************//**
 * @file   Coordinate.h
 * @brief  Structure for storing Coordinate.
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_COORDINATE_H
#define GUARD_COORDINATE_H

struct Coordinate
{
    Coordinate(float latitude, float longitude)
        : latitude(latitude), longitude(longitude)
    {
    }

    float latitude;
    float longitude;
};


#endif // !GUARD_COORDINATE_H