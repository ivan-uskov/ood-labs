#include "stdafx.h"
#include "Duck.h"

using namespace std;

Duck::Duck(unique_ptr<IFlyBehavior> && flyBehavior, unique_ptr<IQuackBehavior> && quackBehavior)
    : m_quackBehavior(move(quackBehavior))
{
    assert(m_quackBehavior);
    SetFlyBehavior(move(flyBehavior));
}

void Duck::Quack() const
{
    m_quackBehavior->Quack();
}

void Duck::Swim()
{
    cout << "I'm swimming" << endl;
}

void Duck::Fly()
{
    m_flyBehavior->Fly();
}

void Duck::Dance()
{
    if (m_danceBehavior)
    {
        m_danceBehavior();
    }
}

void Duck::SetFlyBehavior(unique_ptr<IFlyBehavior> && flyBehavior)
{
    assert(flyBehavior);
    m_flyBehavior = move(flyBehavior);
}

void Duck::SetDanceBehavior(DanceBehavior danceBehavior)
{
    m_danceBehavior = danceBehavior;
}