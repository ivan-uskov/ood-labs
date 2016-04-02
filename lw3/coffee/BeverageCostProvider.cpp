#include "BeverageCostProvider.h"
#include <stdexcept>

using namespace std;

namespace
{
    double GetCoffeeCost(const BeverageQuantity & quantity)
    {
        return 1;
    }

    double GetTeaCost(const BeverageQuantity & quantity)
    {
        return 1;
    }
}

namespace BeverageCostProvider
{
    double GetBaseBeverageCost(const BeverageType & type, const BeverageQuantity & quantity)
    {
        switch (type)
        {
        case BeverageType::Coffee:
            return 60;
        case BeverageType::Latte:
            return 90;
        case BeverageType::Cappuchino:
            return 80;
        case BeverageType::Tea:
            return 30;
        case BeverageType::Milkshake:
            return 80;
        default:
            throw invalid_argument("Invalid beverage type!");
        }
    }
}