#include "stdafx.h"
#include "DeckoyDuck.h"

using namespace std;

DeckoyDuck::DeckoyDuck()
    : Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>())
{
}

void DeckoyDuck::Display() const
{
    cout << "I'm deckoy duck" << endl;
}
