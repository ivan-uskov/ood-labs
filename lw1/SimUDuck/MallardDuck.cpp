#include "stdafx.h"
#include "MallardDuck.h"

using namespace std;

MallardDuck::MallardDuck()
{
    SetQuackBehavior(QuackStrategy::Quack);
    SetFlyBehavior(FlyStrategy::FlyWithWings());
    SetDanceBehavior(DanceStrategy::Waltz);
}

void MallardDuck::Display() const
{
    cout << "I'm mallard duck" << endl;
}