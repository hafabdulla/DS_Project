/*****************************************************************//**
 * @file   main.cpp
 * @brief  Application Entry Point (Presentation Layer).
 *
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#include <iostream>
#include <string>
#include <Infrastructure/CCsvBusRepository.h>
#include <Domain/TransportService.h>

using namespace std;

int main()
{
    TransportService transportService;
    transportService.UpdateBusLocation("B402", "Stop6");

    const Stack<std::string>* history = transportService.GetBusRouteHistory("B402");

    for (auto& stop : (*history))
    {
        std::cout << stop << std::endl;
    }

    return 0;
}