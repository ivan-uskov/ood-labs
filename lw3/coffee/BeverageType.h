#pragma once
#include <iostream>

enum class BeverageType
{
    Coffee,
    Cappuchino,
    Latte,
    Tea,
    RedTea,
    GreenTea,
    YellowTea,
    Milkshake
};

std::ostream & operator << (std::ostream & out, const BeverageType & beverageType);