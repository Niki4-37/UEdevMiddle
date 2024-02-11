#pragma once

#include <ctime>
#include "Vehicle.h"

float  getHighestPower(const std::vector<Vehicle*>& vehicles)
{
    if (vehicles.empty()) return 0.f;
    float maxPower{};
    for (const auto vehicle : vehicles)
    {
        if (!vehicle) continue;
        if (maxPower < vehicle->getPower())
        {
            maxPower = vehicle->getPower();
        }
    }
    return maxPower;
}

int main()
{
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);

    std::cout << c << '\n';

    Bicycle t(Wheel(20), Wheel(20), 300);

    std::cout << t << '\n';


    std::vector<Vehicle*> v;

    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));

    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));

    v.push_back(new WaterVehicle(5000));

    for (const auto vehicle : v)
    {
        if (!vehicle) continue;
        std::cout << *vehicle << '\n';
    }

    std::cout << "The highest power is " << getHighestPower(v);

    v.clear();

    return 0;
}