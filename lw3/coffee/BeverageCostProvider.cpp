#include "BeverageCostProvider.h"
#include <stdexcept>
#include <algorithm>
#include <map>

using namespace std;

namespace
{
    template <typename MapType, typename KeyType>
    auto GetMapValue(MapType const& srcMap, KeyType const& key)
    {
        auto pairIt = srcMap.find(key);

        if (pairIt == srcMap.end())
        {
            throw invalid_argument("Unexpected key specified!");
        }

        return pairIt->second;
    }

    typedef map<BeverageQuantity, double> CostInfoByQuantityMap;

    static const CostInfoByQuantityMap coffeeMap = {
        {BeverageQuantity::Standard, 60}
    };

    static const CostInfoByQuantityMap latteMap = {
        { BeverageQuantity::Standard, 90  },
        { BeverageQuantity::Duo,      130 }
    };

    static const CostInfoByQuantityMap cappuchinoMap = {
        { BeverageQuantity::Standard, 80  },
        { BeverageQuantity::Duo,      120 }
    };

    static const CostInfoByQuantityMap teaMap = {
        { BeverageQuantity::Standard, 30 }
    };

    static const CostInfoByQuantityMap milkshakeMap = {
        { BeverageQuantity::Small,    50 },
        { BeverageQuantity::Standard, 60 },
        { BeverageQuantity::Big,      80 }
    };

    static const map<BeverageType, CostInfoByQuantityMap const&> costInfoByTypeMap = {
        { BeverageType::Coffee,     coffeeMap     },
        { BeverageType::Latte,      latteMap      },
        { BeverageType::Cappuchino, cappuchinoMap },
        { BeverageType::Tea,        teaMap        },
        { BeverageType::RedTea,     teaMap        },
        { BeverageType::GreenTea,   teaMap        },
        { BeverageType::YellowTea,  teaMap        },
        { BeverageType::Milkshake,  milkshakeMap  }
    };
}

namespace BeverageCostProvider
{
    double GetBaseBeverageCost(const BeverageType & type, const BeverageQuantity & quantity)
    {
        return GetMapValue(GetMapValue(costInfoByTypeMap, type), quantity);
    }
}