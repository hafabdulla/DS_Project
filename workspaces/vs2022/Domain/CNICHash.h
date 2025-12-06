/*****************************************************************//**
 * @file   CNICHash.h
 * @brief  
 * 
 * @author Fahad Hassan
 * @date   03 12 2025
 *********************************************************************/

#ifndef GUARD_CNICHASH_H
#define GUARD_CNICHASH_H

#include <Domain/Person.h>
#include <string>
#include <cstddef>

struct CNICHash
{
    std::size_t operator()(const CNIC& cnic) const;
};

#endif // !GUARD_CNICHASH_H

