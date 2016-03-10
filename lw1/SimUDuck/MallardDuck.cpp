#include "stdafx.h"
#include "MallardDuck.h"

using namespace std;

MallardDuck::MallardDuck()
    : Duck(make_unique<QuackBehavior>())
{
    SetFlyBehavior(FlyWithWings());
}

void MallardDuck::Display() const
{
    cout << "I'm mallard duck" << endl;
}