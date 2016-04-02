#include "BeverageQuantity.h"

using namespace std;

ostream & operator << (ostream & out, BeverageQuantity const& quantity)
{
    switch (quantity)
    {
    case BeverageQuantity::Small:
        out << "Small";
        break;
    case BeverageQuantity::Standard:
        out << "Standard";
        break;
    case BeverageQuantity::Big:
        out << "Big";
        break;
    case BeverageQuantity::Duo:
        out << "Duo";
        break;
    }

    return out;
}