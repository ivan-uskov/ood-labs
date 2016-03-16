#include "stdafx.h"
#include "RubberDuck.h"

using namespace std;

RubberDuck::RubberDuck()
{
    SetQuackBehavior(QuackStrategy::Quack);
}

void RubberDuck::Display() const
{
    cout << "I'm rubber duck" << endl;
}