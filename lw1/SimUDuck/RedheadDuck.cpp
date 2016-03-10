#include "stdafx.h"
#include "RedheadDuck.h"

using namespace std;

RedheadDuck::RedheadDuck()
    : Duck(make_unique<QuackBehavior>())
{
    SetFlyBehavior(FlyWithWings());
}

void RedheadDuck::Display() const
{
    cout << "I'm redhead duck" << endl;
}