#pragma once
#include <iostream>

struct paperUnitInfo
{
    uint32_t circulation{};
    uint32_t pages{};
    std::string title{ "none" };
    std::string authors{ "none" };
    std::string publisherName{ "none" };
    std::string unitType{ "none" };

    friend std::ostream& operator<<(std::ostream& out, const paperUnitInfo& info);
};

std::ostream& operator<<(std::ostream& out, const paperUnitInfo& info)
{
    out << info.unitType << '\n'
        << info.title << '\n'
        << "Authors: " << info.authors << '\n'
        << "Pages: " << info.pages << '\n'
        << "Circulation: " << info.circulation << '\n'
        << info.publisherName << '\n';
    return out;
}

class PaperUnit
{
public:
    PaperUnit();
    virtual ~PaperUnit() { delete Info; };
    void printInfo() const { if (Info) { std::cout << *Info; } };

protected:
    paperUnitInfo* Info{ nullptr };
};

PaperUnit::PaperUnit()
{
    Info = new paperUnitInfo;
}

class Book : public PaperUnit
{
public:
    Book(paperUnitInfo* info)
    {
        if (info)
        {
            new(Info) paperUnitInfo(*info);
        }
        Info->unitType = "Book";
    }
private:
    Book();
};

class Magazine : public PaperUnit {};
class Newspaper : public PaperUnit {};
class Comics : public PaperUnit {};

class IPublisher
{
public:
    virtual PaperUnit* publishBook(paperUnitInfo* info) = 0;
    virtual PaperUnit* publishMagazine() = 0;
    virtual PaperUnit* publishNewspaper() = 0;
    virtual PaperUnit* publishComics() = 0;
};

class FutureMehanicFiction : public IPublisher
{
public:
    virtual PaperUnit* publishBook(paperUnitInfo* info) override;
    virtual PaperUnit* publishMagazine() override { return new Magazine; };
    virtual PaperUnit* publishNewspaper() override { return new Newspaper; };
    virtual PaperUnit* publishComics() override { return new Comics; };
};

PaperUnit* FutureMehanicFiction::publishBook(paperUnitInfo* info)
{
    info->publisherName = "Future Mehanic Fiction";
    return new Book{ info };
}

class UrbanStylePublisher : public IPublisher {};

//int main()
//{
//    auto futureGear = new paperUnitInfo;
//    futureGear->title = "FutureGear";
//    futureGear->authors = "F.J.Thomphson";
//    futureGear->circulation = 1000;
//    futureGear->pages = 250;
//
//    auto futureFiction = new FutureMehanicFiction;
//    if (futureFiction)
//    {
//        auto bookFutureGear = futureFiction->publishBook(futureGear);
//        if (bookFutureGear)
//        {
//            bookFutureGear->printInfo();
//        }
//
//        delete bookFutureGear;
//    }
//
//    delete futureFiction;
//    delete futureGear;
//    return 0;
//}