#pragma once
#include <iostream>
#include <stdexcept>

class Fraction
{
public:
    Fraction(int numerator, int denominator) : numerator{ numerator }, denominator{ denominator }
    {
        if (!denominator)
        {
            throw std::runtime_error("denominator is zero!");
        }

    };

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fr);

private:
    int numerator{}, denominator{};
};

std::ostream& operator<<(std::ostream& out, const Fraction& fr)
{
    out << fr.numerator << '/' << fr.denominator << '\n';
    return out;
}