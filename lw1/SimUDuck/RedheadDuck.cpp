#include "stdafx.h"
#include "RedheadDuck.h"

using namespace std;

RedheadDuck::RedheadDuck()
    : Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>())
{
}

void RedheadDuck::Display() const
{
    cout << "I'm redhead duck" << endl;
}