/*****************************************************************//**
 * @file   Coordinate.h
 * @brief  Structure for storing Coordinate.
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_COORDINATE_H
#define GUARD_COORDINATE_H

#include <cmath>

constexpr double R = 6371.0;
constexpr double TO_RAD = 3.1415926535 / 180.0;

struct Coordinate
{
    double latitude;
    double longitude;

    Coordinate(double latitude, double longitude)
        : latitude(latitude), longitude(longitude)
    {
    }

    double DistanceTo(const Coordinate& other) const
    {
        double dLat = (other.latitude - latitude) * TO_RAD;
        double dLon = (other.longitude - longitude) * TO_RAD;

        double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
            std::cos(latitude * TO_RAD) * std::cos(other.latitude * TO_RAD) *
            std::sin(dLon / 2) * std::sin(dLon / 2);

        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

        return R * c;
    }
};

#endif // !GUARD_COORDINATE_H