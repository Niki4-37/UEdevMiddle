#pragma once
#include <vector>
#include "StrategyUnitsFactory.h"

// Singleton
class BattleDirector
{
public:
    static BattleDirector* getBattleDirector();
    void startBattleBetween(                    //
        IFraction* fractionOne,                 //
        std::vector<CombatUnitData*> dataOne,   //
        IFraction* fractionTwo,                 //
        std::vector<CombatUnitData*> dataTwo);

private:
    BattleDirector() { };
    ~BattleDirector() { };
    static BattleDirector* instance;
};

BattleDirector* BattleDirector::instance = nullptr;

inline BattleDirector* BattleDirector::getBattleDirector()
{
    if (!instance)
    {
        instance = new BattleDirector;
    }
    return instance;
}

void BattleDirector::startBattleBetween(    //
    IFraction* fractionOne,                 //
    std::vector<CombatUnitData*> dataOne,   //
    IFraction* fractionTwo,                 //
    std::vector<CombatUnitData*> dataTwo)
{
    // create army
    if (fractionOne)
    {
        for (const auto unitData : dataOne)
        {
            if (!unitData) continue;
            const auto unitFractionOne = fractionOne->createCombatUnit(unitData);
            if (!unitFractionOne) continue;
            // adding to ARMY ARRAY for using in battle process

            delete unitFractionOne; //avoid memory leak, remove if using ARMY ARRAY
        }
    }

    if (fractionTwo)
    {
        for (const auto unitData : dataTwo)
        {
            if (!unitData) continue;
            const auto unitFractionTwo = fractionTwo->createCombatUnit(unitData);
            if (!unitFractionTwo) continue;
            // adding to ARMY ARRAY for using in battle process

            delete unitFractionTwo; //avoid memory leak, remove if using ARMY ARRAY
        }
    }
}