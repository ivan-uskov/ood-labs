#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
    return [=](auto && b) {
        return make_unique<Condiment>(forward<decltype(b)>(b), args...);
    };
}

auto ChangeQuantity(const BeverageQuantity & quantity)
{
    return [=](auto && b) {
        b->SetQuantity(quantity);
        return move(b);
    };
}

template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
    return decorate(forward<Component>(component));
}

int main()
{
    {
        auto beverage =
            make_unique<CLatte>()
            << ChangeQuantity(BeverageQuantity::Duo)
            << MakeCondiment<CCinnamon>()
            << MakeCondiment<CLemon>(2)
            << MakeCondiment<CIceCubes>(2, IceCubeType::Dry)
            << MakeCondiment<CChocolateCrumbs>(2);

        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
    }

    {
        auto beverage =
            make_unique<CMilkshake>()
            << ChangeQuantity(BeverageQuantity::Big)
            << MakeCondiment<CCinnamon>()
            << MakeCondiment<CLemon>(2)
            << MakeCondiment<CIceCubes>(2, IceCubeType::Dry)
            << MakeCondiment<CChocolateCrumbs>(2);

        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
    }

    {
        auto beverage =
            make_unique<CRedTea>()
            << MakeCondiment<CCinnamon>()
            << MakeCondiment<CLemon>(2)
            << MakeCondiment<CIceCubes>(2, IceCubeType::Dry)
            << MakeCondiment<CChocolateCrumbs>(2);

        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
    }

    {
        auto beverage =
            make_unique<CMilkshake>()
            << MakeCondiment<CSyrup>(SyrupType::Maple)
            << MakeCondiment<CCream>(200)
            << MakeCondiment<CCoconutFlakes>(8);

        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
    }

    {
        auto beverage =
            make_unique<CMilkshake>()
            << MakeCondiment<CSyrup>(SyrupType::Maple)
            << MakeCondiment<CCoconutFlakes>(8)
            << MakeCondiment<CChocolatePices>(4)
            << MakeCondiment<CLiquor>(LiquorType::Chocolate);
        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
    }
}
