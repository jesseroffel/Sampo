#include "sampo_pch.hpp"
#include "vector3_io.hpp"

namespace Sampo
{ 
    std::ostream& operator<<(std::ostream& os, const Vector2 vec)
    {
        os << '{' << vec.x << ", " << vec.y << '}';
        return os;
    }
}