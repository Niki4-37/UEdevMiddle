#pragma once
#include <memory>
#include "Fraction.h"

int main()
{
    int a, b;
    std::cout << "enter numerator: ";
    std::cin >> a;
    std::cout << "\nenter denominator: ";
    std::cin >> b;

    try
    {
        std::unique_ptr<Fraction> u_ptr_fraction1{ new Fraction(a, b) };
        std::cout << *u_ptr_fraction1;
    }
    catch (std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
    }

    return 0;
}