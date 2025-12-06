/*****************************************************************//**
 * @file   CCsvBusRepository.h
 * @brief  CSV implementation of the Bus Repository.
 * 
 * @author Fahad Hassan
 * @date   1 12 2025
 *********************************************************************/

#ifndef GUARD_CCSVREPOSITORY_H
#define GUARD_CCSVREPOSITORY_H

#include <string>
#include <Domain/IBusRepository.h>

class CCsvBusRepository : public IBusRepository
{
private:
    std::string m_FilePath;

    void ParseRoute(Bus& bus, const std::string& routeStr) const;

public:
    explicit CCsvBusRepository(const std::string& filePath);

    LinkedList<Bus> LoadAll() override;
};

#endif // !GUARD_CCSVREPOSITORY_H
