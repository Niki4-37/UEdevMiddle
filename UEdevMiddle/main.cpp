#pragma once

#include <ctime>
#include "Vector.h"
#include "ComplexObject.h"

int main()
{
    srand(time(0));
    char newObjectName[]{ "Pear" };
    auto vec1 = new Vector(5.5f, -4.1f, .5f);
    ComplexObject newObject(newObjectName, 4, vec1);
    delete vec1;

    for (; newObject.push(rand() % 201 - 100);) {};
    std::cout << newObject << '\n';

    char zeroObjectName[]{ "Zero" };
    vec1 = new Vector();
    ComplexObject zeroObject(zeroObjectName, 3, vec1);
    delete vec1;
    std::cout << zeroObject << '\n';

    ComplexObject copyNewObject{ zeroObject };
    std::cout << copyNewObject << '\n';

    copyNewObject = newObject;
    std::cout << copyNewObject << '\n';

    return 0;
}