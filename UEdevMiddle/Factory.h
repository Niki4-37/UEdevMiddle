#pragma once
#include<iostream>

enum class CellType : uint8_t
{
    Empty = 0,
    ExtraLive = 1,
    Food = 2,
    MAX_NUM = 3,

    Body
};

class Cell
{
public:
    virtual void printSymbol() = 0;
    virtual CellType getType() const = 0;
};

class Empty : public Cell
{
public:
    virtual void printSymbol() override { std::cout << symbol; };
    virtual CellType getType() const override { return CellType::Empty; };
private:
    char symbol{ ' ' };
};

class ExtraLive : public Cell
{
public:
    virtual void printSymbol() override { std::cout << symbol; };
    virtual CellType getType() const override { return CellType::ExtraLive; };

private:
    char symbol{ '+' };
};

class Food : public Cell
{
public:
    virtual void printSymbol() override { std::cout << symbol; };
    virtual CellType getType() const override { return CellType::Food; };

private:
    char symbol{ '@' };
};

class Body : public Cell
{
public:
    virtual void printSymbol() override { std::cout << symbol; };
    virtual CellType getType() const override { return CellType::Body; };

private:
    char symbol{ '*' };
};


class IFieldCreator
{
public:
    virtual Cell* createCell(CellType Type);
};

Cell* IFieldCreator::createCell(CellType Type)
{
    Cell* newCell{ nullptr };
    switch (Type)
    {
    case CellType::Empty: return new Empty;
    case CellType::ExtraLive: return new ExtraLive;
    case CellType::Food: return new Food;
    default: return new Empty;
    }
}

//int main()
//{
//    srand(time(0));
//    int a, b;
//    std::cout << "enter field width: ";
//    std::cin >> a;
//    std::cout << "\nenter field height: ";
//    std::cin >> b;
//
//    std::vector<Cell*> Field;
//    Field.reserve(a * b);
//
//    const auto fieldCreator = new IFieldCreator;
//    int iii{};
//    if (fieldCreator)
//    {
//        while (iii < a * b)
//        {
//            int randCellType = rand() % (static_cast<int>(CellType::MAX_NUM));
//            auto newCell = fieldCreator->createCell(static_cast<CellType>(randCellType));
//            if (!newCell) continue;
//            Field.push_back(newCell);
//            ++iii;
//        }
//    }
//    iii = 0;
//    if (Field.size() > 0)
//    {
//        for (const auto Cell : Field)
//        {
//            if (!Cell) continue;
//            if (iii % a == 0) { std::cout << '\n'; }
//            Cell->printSymbol();
//            ++iii;
//        }
//    }
//
//    delete fieldCreator;
//
//    return 0;
//}
