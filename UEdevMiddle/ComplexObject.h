#pragma once

#include "Vector.h"
#include <iostream>
#include <cstring>

class ComplexObject
{
public:
    ComplexObject() = delete;
    ComplexObject(char* name, int Size, Vector* newVector);
    ComplexObject(const ComplexObject& other);

    ~ComplexObject();

    ComplexObject& operator=(const ComplexObject& other);
    friend std::ostream& operator<<(std::ostream& out, const ComplexObject& object);

    int getRows() const { return rows; };
    int getColumns() const { return columns; };

    bool push(int value);

private:
    char* objectName{ nullptr };

    int rows{}, columns{};
    int** complexArray{ nullptr };
    int arrayIndex{};

    Vector* vector{ nullptr };

    void deletComplexArray();
};

ComplexObject::ComplexObject(char* name, int Size, Vector* newVector = nullptr)
{
    if (name)
    {
        const size_t nameLenght = std::strlen(name) + 1;
        objectName = new char[nameLenght];

        for (size_t charIndex{}; charIndex < nameLenght; ++charIndex)
        {
            objectName[charIndex] = name[charIndex];
        }
    }

    if (Size > 0)
    {
        rows = columns = Size;
        complexArray = new int* [rows] {};
        for (int rowIndex{}; rowIndex < rows; ++rowIndex)
        {
            complexArray[rowIndex] = new int[columns] {};
        }
    }

    if (newVector)
    {
        vector = new Vector(*newVector);
    }
}

ComplexObject::ComplexObject(const ComplexObject& other)
{
    std::cout << "copy const\n";

    if (other.objectName)
    {
        const size_t nameLenght = std::strlen(other.objectName) + 1;
        objectName = new char[nameLenght];

        for (size_t charIndex{}; charIndex < nameLenght; ++charIndex)
        {
            objectName[charIndex] = other.objectName[charIndex];
        }
    }

    if (other.complexArray)
    {
        rows = other.getRows();
        columns = other.getColumns();
        complexArray = new int* [rows] {};
        for (int rowIndex{}; rowIndex < rows; ++rowIndex)
        {
            complexArray[rowIndex] = new int[rows] {};
            for (int columnIndex{}; columnIndex < columns; ++columnIndex)
            {
                complexArray[rowIndex][columnIndex] = other.complexArray[rowIndex][columnIndex];
            }
        }
    }

    if (other.vector)
    {
        vector = new Vector(*other.vector);
    }
}

ComplexObject::~ComplexObject()
{
    delete[] objectName;
    deletComplexArray();
    delete vector;
}

ComplexObject& ComplexObject::operator=(const ComplexObject& other)
{
    std::cout << "copy assignment\n";

    if (other.objectName)
    {
        delete[] objectName;
        const size_t nameLenght = std::strlen(other.objectName) + 1;
        objectName = new char[nameLenght];

        for (size_t charIndex{}; charIndex < nameLenght; ++charIndex)
        {
            objectName[charIndex] = other.objectName[charIndex];
        }
    }

    if (other.complexArray)
    {
        deletComplexArray();

        rows = other.getRows();
        columns = other.getColumns();
        complexArray = new int* [rows];
        for (int rowIndex{}; rowIndex < rows; ++rowIndex)
        {
            complexArray[rowIndex] = new int[columns];
            for (int columnIndex{}; columnIndex < columns; ++columnIndex)
            {
                complexArray[rowIndex][columnIndex] = other.complexArray[rowIndex][columnIndex];
            }
        }
    }

    if (other.vector)
    {
        delete vector;
        vector = new Vector(*other.vector);
    }

    return *this;
}

std::ostream& operator<<(std::ostream& out, const ComplexObject& object)
{
    if (object.objectName)
    {
        out << "Object: " << object.objectName << '\n';
    }

    if (object.complexArray)
    {
        for (int rowIndex{}; rowIndex < object.rows; ++rowIndex)
        {
            for (int columnIndex{}; columnIndex < object.columns; ++columnIndex)
            {
                out << object.complexArray[rowIndex][columnIndex] << ' ';
            }
            out << '\n';
        }
    }

    if (object.vector)
    {
        out << "Vector:\n" << *object.vector << '\n';
    }

    return out;
}

inline bool ComplexObject::push(int value)
{
    if (!complexArray || arrayIndex >= rows * columns) return false;

    if (!arrayIndex)
    {
        complexArray[0][0] = value;
        ++arrayIndex;
    }
    else
    {
        const int rowIndex = arrayIndex / rows;
        const int columnIndex = arrayIndex % columns;
        complexArray[rowIndex][columnIndex] = value;
        ++arrayIndex;
    }
    return true;
}

void ComplexObject::deletComplexArray()
{
    if (!complexArray) return;

    for (int rowIndex{}; rowIndex < rows; ++rowIndex)
    {
        if (!complexArray[rowIndex]) continue;
        delete[] complexArray[rowIndex];
    }

    delete[] complexArray;
}