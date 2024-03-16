#pragma once
#include <iostream>

enum class unitType : uint8_t
{
    INFANTRY,
    MARKSMAN,
    CAVALRY,
    ARTILLERY,
    none
};

struct CombatUnitData
{
    CombatUnitData(unitType inType = unitType::none, uint8_t inMorale = 0, uint8_t inAttack = 0, uint8_t inDefence = 0, uint32_t inCurrentCount = 0, uint32_t inMaxCount = 0) :
        type{ inType },
        morale{ inMorale },
        attack{ inAttack },
        defence{ inDefence },
        currentCount{ inCurrentCount },
        maxCount{ inMaxCount }
    {}

private:
    unitType type{ unitType::none };
    uint8_t morale{};
    uint8_t attack{};
    uint8_t defence{};
    uint32_t currentCount{};
    uint32_t maxCount{};

public:
    unitType getUnitType() { return type; };
    uint32_t getCurrentCount() { return currentCount; };
};

class Weapon 
{
public:
    Weapon() {};
};

class Uniform 
{
public:
    Uniform() {};
};

struct ViewData
{
    ViewData(Weapon* weaponToAdd, Uniform* uniformToAdd)
    {
        if (weaponToAdd)
        {
            weaponMesh = new Weapon(*weaponToAdd);
        }
        if (uniformToAdd)
        {
            uniformMesh = new Uniform(*uniformToAdd);
        }
    }
    ~ViewData() { delete weaponMesh; delete uniformMesh; }
    Weapon* weaponMesh{ nullptr };
    Uniform* uniformMesh{ nullptr };
};