/*****************************************************************//**
 * @file   StringHash.h
 * @brief  Hash function for strings
 * 
 * @author Fahad Hassan
 * @date   08 12 2025
 *********************************************************************/

#ifndef GUARD_STRINGHASH_H
#define GUARD_STRINGHASH_H

#include <string>

struct StringHash
{
    size_t operator()(const std::string& key) const
    {
        size_t hash = 5381;

        for (char c : key)
            hash = ((hash << 5) + hash) + c;

        return hash;
    }
};

#endif // !GUARD_STRINGHASH_H