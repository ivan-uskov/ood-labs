#include "stdafx.h"
#include "ModelDuck.h"

using namespace std;

ModelDuck::ModelDuck()
{
    SetQuackBehavior(QuackStrategy::Quack);
}

void ModelDuck::Display() const
{
    cout << "I'm model duck" << endl;
}