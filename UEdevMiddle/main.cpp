#pragma once
#include "CoreTypes.h"
#include "BattleDirector.h"
#include "StrategyUnitsFactory.h"

int main()
{
    // loading battle using BattleUnitData array for fractions from side source
    std::vector<CombatUnitData*> France;
    France.push_back(new CombatUnitData(unitType::INFANTRY, 10, 5, 10, 10, 10));
    France.push_back(new CombatUnitData(unitType::CAVALRY, 10, 10, 15, 10, 10));

    std::vector<CombatUnitData*> German;
    German.push_back(new CombatUnitData(unitType::INFANTRY, 8, 5, 10, 7, 10));
    German.push_back(new CombatUnitData(unitType::MARKSMAN, 5, 7, 5, 5, 10));
    German.push_back(new CombatUnitData(unitType::ARTILLERY, 5, 7, 5, 5, 5));

    const auto franceForces = new FranceForces;
    const auto germanForces = new GermanForces;

    if (BattleDirector::getBattleDirector())
    {
        BattleDirector::getBattleDirector()->startBattleBetween(franceForces, France, germanForces, German);
    }

    delete germanForces;
    delete franceForces;

    return 0;
}