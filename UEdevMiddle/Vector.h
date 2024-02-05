#pragma once
#include <iostream>

class Vector
{
public:
    Vector() : x{ 0.f }, y{ 0.f }, z{ 0.f } {};
    Vector(float x, float y, float z) : x{ x }, y{ y }, z{ z } {};

    friend Vector operator+(const Vector& v1, const  Vector& v2);
    friend std::ostream& operator<<(std::ostream& out, const Vector& v);

private:
    float x, y, z;
};

Vector operator+(const Vector& v1, const  Vector& v2)
{
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z;
    return out;
}