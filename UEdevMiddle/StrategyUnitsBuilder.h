#pragma once
#include <iostream>
#include <vector>
#include "CoreTypes.h"

struct CombatUnitData;
struct ViewData;
class Weapon;
class Uniform;

//~~~~~~ Prototype
class Soldier
{
public:
    Soldier() {};
    virtual ~Soldier() {};

    virtual Soldier* clone() { return nullptr; };
    void updateView(const ViewData& data)
    {
        attachWeapon(data.weaponMesh);
        putUniform(data.uniformMesh);
    };

private:
    virtual void attachWeapon(Weapon* newWeapon) {};
    virtual void putUniform(Uniform* newUniform) {};

    //protected:
        // SkeletalMesh* human_mesh;
        // Animation* animation;
};

class InfantrySoldier : public Soldier
{
public:
    InfantrySoldier() { /* create human mesh */  std::cout << "InfantrySoldier\n"; }

    virtual Soldier* clone() override { std::cout << "clone InfantrySoldier\n"; return this; }

private:
    virtual void attachWeapon(Weapon* newWeapon) override {};
    virtual void putUniform(Uniform* newUniform) override {};
};

class MarksmanSoldier : public Soldier 
{
public:
    MarksmanSoldier() { std::cout << "MarksmanSoldier\n"; }

    virtual Soldier* clone() override { std::cout << "clone MarksmanSoldier\n"; return this; }

private:
    virtual void attachWeapon(Weapon* newWeapon) override {};
    virtual void putUniform(Uniform* newUniform) override {};
};

class CavalrySoldier : public Soldier 
{ /* skeletal_mesh* horse_mesh */ 
public:
    CavalrySoldier() { std::cout << "CavalrySoldier\n"; }

    virtual Soldier* clone() override { std::cout << "clone CavalrySoldier\n"; return this; }

private:
    virtual void attachWeapon(Weapon* newWeapon) override {};
    virtual void putUniform(Uniform* newUniform) override {};
};

class CannonCrew : public Soldier 
{ /* Weapon is a cannon */ 
public:
    CannonCrew() { std::cout << "CannonCrew\n"; }

    virtual Soldier* clone() override { std::cout << "clone CannonCrew\n"; return this; }

private:
    virtual void attachWeapon(Weapon* newWeapon) override {};
    virtual void putUniform(Uniform* newUniform) override {};
};

class SoldierSpawner
{
public:
    SoldierSpawner(Soldier* newPrototype)
    {
        prototype = newPrototype;
    }
    ~SoldierSpawner() { }

    Soldier* spawnSoldier() { return prototype->clone(); }

private:
    Soldier* prototype{ nullptr };
};
//~~~~~ end prototype

//~~~~~ Builder
class ICreateCombatUnit
{
public:
    virtual void createPrototype(Soldier* soldierPrototype) = 0;
    virtual void updateViewCollection(const std::vector<ViewData>&) = 0;
    virtual void gatherUnit(uint8_t) = 0;
    virtual const std::vector<Soldier*>& getSoldiers() const = 0;
};

class FranceCombatUnitCreator : public ICreateCombatUnit
{
public:
    ~FranceCombatUnitCreator()
    {
        Soldiers.clear();
        delete spawner;
    }
private:
    virtual void createPrototype(Soldier* soldierPrototype) override { spawner = new SoldierSpawner(soldierPrototype); };
    virtual void updateViewCollection(const std::vector<ViewData>& newCollection) override { viewCollection = newCollection; }
    virtual void gatherUnit(uint8_t totalCount) override;
public:
    virtual const std::vector<Soldier*>& getSoldiers() const override { return Soldiers; }

    SoldierSpawner* spawner{ nullptr };
    std::vector<ViewData> viewCollection {ViewData(new Weapon, new Uniform)};
    std::vector<Soldier*> Soldiers;
};

void FranceCombatUnitCreator::gatherUnit(uint8_t totalCount)
{
    if (totalCount == 0) return;
    Soldiers.reserve(static_cast<size_t>(totalCount));
    uint8_t counter{};
    while (counter < totalCount)
    {
        const auto newSoldier = spawner->spawnSoldier();
        if (!newSoldier) continue;
        const int randomIndex{ /* random generator*/ };
        newSoldier->updateView(viewCollection[randomIndex]);
        Soldiers.push_back(newSoldier);
        ++counter;
    }
}

class GermanCombatUnitCreator : public ICreateCombatUnit
{
public:
    ~GermanCombatUnitCreator()
    {
        Soldiers.clear();
        delete spawner;
    }
private:
    virtual void createPrototype(Soldier* soldierPrototype) override { spawner = new SoldierSpawner(soldierPrototype); };
    virtual void updateViewCollection(const std::vector<ViewData>& newCollection) override { viewCollection = newCollection; }
    virtual void gatherUnit(uint8_t totalCount) override;
public:
    virtual const std::vector<Soldier*>& getSoldiers() const override { return Soldiers; }

    SoldierSpawner* spawner{ nullptr };
    std::vector<ViewData> viewCollection {ViewData(new Weapon, new Uniform)};
    std::vector<Soldier*> Soldiers;
};

void GermanCombatUnitCreator::gatherUnit(uint8_t totalCount)
{
    if (totalCount == 0) return;
    Soldiers.reserve(static_cast<size_t>(totalCount));
    uint8_t counter{};
    while (counter < totalCount)
    {
        const auto newSoldier = spawner->spawnSoldier();
        if (!newSoldier) continue;
        const int randomIndex{ /* random generator*/ };
        newSoldier->updateView(viewCollection[randomIndex]);
        Soldiers.push_back(newSoldier);
        ++counter;
    }
}

class EnglandCombatUnitCreator : public ICreateCombatUnit
{
public:
    ~EnglandCombatUnitCreator()
    {
        Soldiers.clear();
        delete spawner;
    }
private:
    virtual void createPrototype(Soldier* soldierPrototype) override { spawner = new SoldierSpawner(soldierPrototype); };
    virtual void updateViewCollection(const std::vector<ViewData>& newCollection) override { viewCollection = newCollection; }
    virtual void gatherUnit(uint8_t totalCount) override;
public:
    virtual const std::vector<Soldier*>& getSoldiers() const override { return Soldiers; }

    SoldierSpawner* spawner{ nullptr };
    std::vector<ViewData> viewCollection {ViewData(new Weapon, new Uniform)};
    std::vector<Soldier*> Soldiers;
};

void EnglandCombatUnitCreator::gatherUnit(uint8_t totalCount)
{
    if (totalCount == 0) return;
    Soldiers.reserve(static_cast<size_t>(totalCount));
    uint8_t counter{};
    while (counter < totalCount)
    {
        const auto newSoldier = spawner->spawnSoldier();
        if (!newSoldier) continue;
        const int randomIndex{ /* random generator*/ };
        newSoldier->updateView(viewCollection[randomIndex]);
        Soldiers.push_back(newSoldier);
        ++counter;
    }
}

class UnitDirector
{
public:
    static bool gatherFranceCombatUnit(ICreateCombatUnit* creator, CombatUnitData* unitData, std::vector<Soldier*>& SlodierSquad);
    static bool gatherGermanCombatUnit(ICreateCombatUnit* creator, CombatUnitData* unitData, std::vector<Soldier*>& SlodierSquad);
    static bool gatherEnglandCombatUnit(ICreateCombatUnit* creator, CombatUnitData* unitData, std::vector<Soldier*>& SlodierSquad);
};

bool UnitDirector::gatherFranceCombatUnit(ICreateCombatUnit* creator, CombatUnitData* unitData, std::vector<Soldier*>& SlodierSquad)
{
    if (!creator || !unitData) return false;
    // should be method to get from data table by unitData.type prototype class
    // used switch-case in this way
    Soldier* prototypeClassPtr{ nullptr };
    switch (unitData->getUnitType())
    {
        case unitType::INFANTRY: prototypeClassPtr = new InfantrySoldier; break;
        case unitType::MARKSMAN: prototypeClassPtr = new MarksmanSoldier; break;
        case unitType::CAVALRY: prototypeClassPtr = new CavalrySoldier; break;
        case unitType::ARTILLERY: prototypeClassPtr = new CannonCrew; break;
        default : prototypeClassPtr = nullptr;
    }

    creator->createPrototype(prototypeClassPtr);
    // should be method to get from data table by unitData.type Collection FranceCollectionByType
    //creator->updateViewCollection(FranceCollectionByType);
    creator->gatherUnit(static_cast<uint8_t>(unitData->getCurrentCount()));

    delete prototypeClassPtr;
    SlodierSquad = creator->getSoldiers();
    return true;
}

bool UnitDirector::gatherGermanCombatUnit(ICreateCombatUnit* creator, CombatUnitData* unitData, std::vector<Soldier*>& SlodierSquad)
{
    if (!creator || !unitData) return false;
    // should be method to get from data table by unitData.type prototype class
    // used switch-case in this way
    Soldier* prototypeClassPtr{ nullptr };
    switch (unitData->getUnitType())
    {
        case unitType::INFANTRY: prototypeClassPtr = new InfantrySoldier; break;
        case unitType::MARKSMAN: prototypeClassPtr = new MarksmanSoldier; break;
        case unitType::CAVALRY: prototypeClassPtr = new CavalrySoldier; break;
        case unitType::ARTILLERY: prototypeClassPtr = new CannonCrew; break;
        default : prototypeClassPtr = nullptr;
    }

    creator->createPrototype(prototypeClassPtr);
    // should be method to get from data table by unitData.type Collection GermanCollectionByType
    //creator->updateViewCollection(GermanCollectionByType);
    creator->gatherUnit(static_cast<uint8_t>(unitData->getCurrentCount()));

    delete prototypeClassPtr;
    SlodierSquad = creator->getSoldiers();
    return true;
}

bool UnitDirector::gatherEnglandCombatUnit(ICreateCombatUnit* creator, CombatUnitData* unitData, std::vector<Soldier*>& SlodierSquad)
{
    if (!creator || !unitData) return false;
    // should be method to get from data table by unitData.type prototype class
    // used switch-case in this way
    Soldier* prototypeClassPtr{ nullptr };
    switch (unitData->getUnitType())
    {
        case unitType::INFANTRY: prototypeClassPtr = new InfantrySoldier; break;
        case unitType::MARKSMAN: prototypeClassPtr = new MarksmanSoldier; break;
        case unitType::CAVALRY: prototypeClassPtr = new CavalrySoldier; break;
        case unitType::ARTILLERY: prototypeClassPtr = new CannonCrew; break;
        default : prototypeClassPtr = nullptr;
    }

    creator->createPrototype(prototypeClassPtr);
    // should be method to get from data table by unitData.type Collection EnglandCollectionByType
    //creator->updateViewCollection(EnglandCollectionByType);
    creator->gatherUnit(static_cast<uint8_t>(unitData->getCurrentCount()));

    delete prototypeClassPtr;
    SlodierSquad = creator->getSoldiers();
    return true;
}