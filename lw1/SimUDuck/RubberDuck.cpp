#include "stdafx.h"
#include "RubberDuck.h"

using namespace std;

RubberDuck::RubberDuck()
    : Duck(make_unique<QuackBehavior>())
{
}

void RubberDuck::Display() const
{
    cout << "I'm rubber duck" << endl;
}