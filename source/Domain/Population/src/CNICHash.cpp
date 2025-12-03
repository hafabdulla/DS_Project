#include <Domain/Population/CNICHash.h>

std::size_t CNICHash::operator()(const CNIC& cnic) const
{
    std::size_t hash = 5381;

    for (char c : cnic)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}