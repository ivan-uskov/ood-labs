#include "stdafx.h"
#include "MallardDuck.h"

using namespace std;

MallardDuck::MallardDuck()
    : Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>())
{
}

void MallardDuck::Display() const
{
    cout << "I'm mallard duck" << endl;
}