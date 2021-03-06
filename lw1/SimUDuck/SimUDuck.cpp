#include "stdafx.h"
#include "Duck.h"
#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "DeckoyDuck.h"
#include "RubberDuck.h"
#include "ModelDuck.h"

using namespace std;

void DrawDuck(Duck const& duck)
{
    duck.Display();
}

void PlayWithDuck(Duck & duck)
{
    DrawDuck(duck);
    duck.Quack();
    duck.Dance();
    duck.Fly();
}

void main()
{
    MallardDuck mallarDuck;
    PlayWithDuck(mallarDuck);
    PlayWithDuck(mallarDuck);

    cout << endl;

    RedheadDuck redheadDuck;
    PlayWithDuck(redheadDuck);
    PlayWithDuck(redheadDuck);

    cout << endl;

    RubberDuck rubberDuck;
    PlayWithDuck(rubberDuck);

    cout << endl;

    DeckoyDuck deckoyDuck;
    PlayWithDuck(deckoyDuck);

    cout << endl;

    ModelDuck modelDuck;
    PlayWithDuck(modelDuck);
    modelDuck.SetFlyBehavior(FlyStrategy::FlyWithWings());
    PlayWithDuck(modelDuck);
}