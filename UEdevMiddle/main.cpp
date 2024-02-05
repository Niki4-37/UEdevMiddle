#pragma once
#include "Vector.h"

int main()
{
    Vector v1(3.f, 0.5f, 4.5f);
    Vector v2(1.5f, 3.f, 1.5f);
    Vector v3;
    std::cin >> v3;
    std::cout << v3 - v1;
    return 0;
}