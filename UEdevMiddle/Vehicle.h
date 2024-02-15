#pragma once

#include <iostream>
#include <vector>

class Engine
{
public:
    Engine(float powerValue) : power{ powerValue } {};

    friend std::ostream& operator<<(std::ostream& out, const Engine& engine);
    float getPower() const { return power; }

private:
    float power{};
};

std::ostream& operator<<(std::ostream& out, const Engine& engine)
{
    out << engine.power;
    return out;
}

class Wheel
{
public:
    Wheel(float diameterValue) : diameter{ diameterValue } {};

    friend std::ostream& operator<<(std::ostream& out, const Wheel& wheel);
private:
    float diameter{};
};

std::ostream& operator<<(std::ostream& out, const Wheel& wheel)
{
    out << wheel.diameter;
    return out;
}

class Vehicle
{
public:
    virtual ~Vehicle() {};

    virtual std::ostream& print() const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Vehicle& vehicle);
    virtual float getPower() const = 0;
};

std::ostream& operator<<(std::ostream& out, const Vehicle& vehicle)
{
    return vehicle.print();
}

class WaterVehicle : public Vehicle
{
public:
    WaterVehicle(float draftValue) : vesselDraft{ draftValue } {};
    virtual ~WaterVehicle() {};

    virtual std::ostream& print() const override;
    virtual float getPower() const override;
private:
    float vesselDraft{};
};

std::ostream& WaterVehicle::print() const
{
    return std::cout << "WaterVehicle vessel draft: " << vesselDraft << '\n';
}

float WaterVehicle::getPower() const
{
    return 0.f;
}

class RoadVehicle : public Vehicle
{
public:
    RoadVehicle(float clearanceValue) : clearance{ clearanceValue } {};
    virtual ~RoadVehicle()
    {
        wheels.clear();
    }

    virtual std::ostream& print() const override = 0;

protected:
    std::vector<Wheel> wheels;

    float getClearance() const { return clearance; };

    std::ostream& outWheels(std::ostream& out) const;

private:
    float clearance{};
};

std::ostream& RoadVehicle::outWheels(std::ostream& out) const
{
    for (const auto& wheel : wheels)
    {
        out << wheel << ' ';
    }
    return out;
}

class Bicycle : public RoadVehicle
{
public:
    Bicycle(Wheel frontWheel, Wheel rareWheel, float clearanceValue) : RoadVehicle(clearanceValue)
    {
        wheels.reserve(2);
        wheels.push_back(frontWheel);
        wheels.push_back(rareWheel);
    }

    virtual std::ostream& print() const override;
    virtual float getPower() const override;
};

std::ostream& Bicycle::print() const
{
    return std::cout << "Bicycle wheels: "      //
        << wheels[0] << ' '                     //
        << wheels[1] << ' '                     //
        << "Ride height: " << getClearance();   //
}

float Bicycle::getPower() const
{
    return 0.f;
}

class Car : public RoadVehicle
{
public:
    Car(Engine carEngine, Wheel frontLeftWheel, Wheel frontRightWheel, Wheel rareLeftWheel, Wheel rareRightWheel, float clearanceValue)
        : RoadVehicle(clearanceValue), engine{ carEngine }
    {
        wheels.reserve(4);
        wheels.push_back(frontLeftWheel);
        wheels.push_back(frontRightWheel);
        wheels.push_back(rareLeftWheel);
        wheels.push_back(rareRightWheel);
    };

    virtual std::ostream& print() const override;
    virtual float getPower() const override;

private:
    Engine engine;
};

std::ostream& Car::print() const
{
    return std::cout << "Car Engine: "          //
        << engine << ' '                        //
        << "Wheels" << ' '                      //
        << wheels[0] << ' '                     //
        << wheels[1] << ' '                     //
        << wheels[2] << ' '                     //
        << wheels[3] << ' '                     //
        << "Ride height: " << getClearance();   //
}

float Car::getPower() const
{
    return engine.getPower();
}
