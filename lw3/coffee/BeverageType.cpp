#include "BeverageType.h"
#include <iostream>

using namespace std;

ostream & operator << (ostream & out, const BeverageType & type)
{
    switch (type)
    {
    case BeverageType::Cappuchino:
        out << "Cuppuchino";
        break;
    case BeverageType::Coffee:
        out << "Coffee";
        break;
    case BeverageType::Latte:
        out << "Latte";
        break;
    case BeverageType::Milkshake:
        out << "Milkshake";
        break;
    case BeverageType::Tea:
        out << "Tea";
        break;
    }

    return out;
}