#pragma once
#include <iostream>
#include <cmath>

class Vector
{
public:
    Vector() : x{ 0.f }, y{ 0.f }, z{ 0.f } {};
    Vector(float x, float y, float z) : x{ x }, y{ y }, z{ z } {};

    friend Vector operator+(const Vector& v1, const  Vector& v2);
    friend Vector operator-(const Vector& v1, const  Vector& v2);
    friend std::ostream& operator<<(std::ostream& out, const Vector& v);
    friend std::istream& operator>>(std::istream& in, Vector& inputVector);

    float operator[](int index)
    {
        switch (index)
        {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
            std::cout << "error, wrong index";
            return 0.f;
        }
    }

    operator float()
    {
        std::cout << "vector lenght ";
        return sqrt(x * x + y * y + z * z);
    }

    Vector operator*(int modifier)
    {
        return Vector(x * modifier, y * modifier, z * modifier);
    }

    Vector operator-()
    {
        return Vector(-x, -y, -z);
    }

private:
    float x, y, z;
};

Vector operator+(const Vector& v1, const  Vector& v2)
{
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector operator-(const Vector& v1, const  Vector& v2)
{
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z;
    return out;
}

std::istream& operator>>(std::istream& in, Vector& inputVector)
{
    std::cout << "x value: ";
    in >> inputVector.x;
    std::cout << "y value: ";
    in >> inputVector.y;
    std::cout << "z value: ";
    in >> inputVector.z;
    return in;
}