#include "mathtests.hpp"
#include <foundation/math/vector3.hpp>
#include <foundation/math/vector3_io.hpp>
#include <iostream>

void mathtests::OnAttach()
{
    Sampo::Vector2 a = { 3, 4 };

    auto amag = a.Magnitude();
    std::cout << "a.Magnitude() " << amag << '\n';

    Sampo::Vector2 b = { 12, -5 };
    b.Normalise();
    std::cout << "b.Normalise() " << b << '\n';
}
