#pragma once
#include "BeverageType.h"
#include "BeverageQuantity.h"

namespace BeverageCostProvider
{
    double GetBaseBeverageCost(const BeverageType & type, const BeverageQuantity & quantity);
}