#pragma once

enum class BeverageType
{
    Coffee,
    Cappuchino,
    Latte,
    Tea,
    Milkshake
};

std::ostream & operator << (std::ostream & out, const BeverageType & beverageType);