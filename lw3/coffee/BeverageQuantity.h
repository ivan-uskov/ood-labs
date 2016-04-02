#pragma once
#include <iostream>

enum class BeverageQuantity
{
    Small,
    Standard,
    Big,
    Duo
};

std::ostream & operator << (std::ostream & out, BeverageQuantity const& quantity);