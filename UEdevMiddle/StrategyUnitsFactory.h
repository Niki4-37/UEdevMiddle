#pragma once
#include <iostream>
#include "StrategyUnitsBuilder.h"
#include "CoreTypes.h"

struct CombatUnitData;

// Abstract Factory
class CombatUnit
{
public:
    CombatUnit() { data = new CombatUnitData; };
    virtual ~CombatUnit() { delete data; }

    void setBattleUnitData(CombatUnitData* newData)
    {
        if (!newData) return;
        new (data) CombatUnitData(*newData);
    };

    void addSoldiers(const std::vector<Soldier*>& newSoldiers) { Soldiers = newSoldiers; }

protected:
    CombatUnitData* data{ nullptr };
    std::vector<Soldier*> Soldiers;
};

class InfantrySquad : public CombatUnit
{
public:
    InfantrySquad() { std::cout << "Infantry\n"; }
};

class MarksmanSquad : public CombatUnit
{
public:
    MarksmanSquad() { std::cout << "Marksman\n"; }
};

class CavalrySquad : public CombatUnit
{
public:
    CavalrySquad() { std::cout << "Cavalry\n"; }
};

class ArtillerySection : public CombatUnit
{
public:
    ArtillerySection() { std::cout << "Artillery\n"; }
};

class IFraction
{
public:
    virtual CombatUnit* createCombatUnit(CombatUnitData* newData)
    {
        if (!newData) return nullptr;
        switch (newData->getUnitType())
        {
            case unitType::INFANTRY: return new InfantrySquad;
            case unitType::MARKSMAN: return new MarksmanSquad;
            case unitType::CAVALRY: return new CavalrySquad;
            case unitType::ARTILLERY: return new ArtillerySection;
            default: return nullptr;
        }
    };
};

class FranceForces : public IFraction
{
public:
    FranceForces() { std::cout << "FranceForces\n"; }
private:
    virtual CombatUnit* createCombatUnit(CombatUnitData* newData) override;
};

CombatUnit* FranceForces::createCombatUnit(CombatUnitData* newData)
{
    const auto franceCreator = new FranceCombatUnitCreator;
    const auto combatUnit = IFraction::createCombatUnit(newData);
    if (!franceCreator || !combatUnit) return nullptr;
    combatUnit->setBattleUnitData(newData);
    std::vector<Soldier*> Squad;
    UnitDirector::gatherFranceCombatUnit(franceCreator, newData, Squad);
    combatUnit->addSoldiers(Squad);
    return combatUnit;
}

class GermanForces : public IFraction
{
public:
    GermanForces() { std::cout << "GermanForces\n"; }
private:
    virtual CombatUnit* createCombatUnit(CombatUnitData* newData) override;
};

CombatUnit* GermanForces::createCombatUnit(CombatUnitData* newData)
{
    const auto germanCreator = new GermanCombatUnitCreator;
    const auto combatUnit = IFraction::createCombatUnit(newData);
    if (!germanCreator || !combatUnit) return nullptr;
    combatUnit->setBattleUnitData(newData);
    std::vector<Soldier*> Squad;
    UnitDirector::gatherFranceCombatUnit(germanCreator, newData, Squad);
    combatUnit->addSoldiers(Squad);
    return combatUnit;
}

class EnglandForces : public IFraction
{
public:
    EnglandForces() { std::cout << "EnglandForces\n"; }
private:
    virtual CombatUnit* createCombatUnit(CombatUnitData* newData) override;
};

CombatUnit* EnglandForces::createCombatUnit(CombatUnitData* newData)
{
    const auto englandCreator = new EnglandCombatUnitCreator;
    const auto combatUnit = IFraction::createCombatUnit(newData);
    if (!englandCreator || !combatUnit) return nullptr;
    combatUnit->setBattleUnitData(newData);
    std::vector<Soldier*> Squad;
    UnitDirector::gatherEnglandCombatUnit(englandCreator, newData, Squad);
    combatUnit->addSoldiers(Squad);
    return combatUnit;
}