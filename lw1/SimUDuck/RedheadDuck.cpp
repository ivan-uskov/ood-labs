#include "stdafx.h"
#include "RedheadDuck.h"

using namespace std;

RedheadDuck::RedheadDuck()
{
    SetQuackBehavior(QuackStrategy::Quack);
    SetFlyBehavior(FlyStrategy::FlyWithWings());
    SetDanceBehavior(DanceStrategy::Minuet);
}

void RedheadDuck::Display() const
{
    cout << "I'm redhead duck" << endl;
}