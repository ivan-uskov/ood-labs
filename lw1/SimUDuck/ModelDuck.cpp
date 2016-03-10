#include "stdafx.h"
#include "ModelDuck.h"

using namespace std;

ModelDuck::ModelDuck()
    : Duck(make_unique<QuackBehavior>())
{
}

void ModelDuck::Display() const
{
    cout << "I'm model duck" << endl;
}