#include "stdafx.h"
#include "Duck.h"

using namespace std;

Duck::Duck(unique_ptr<IQuackBehavior> && quackBehavior)
    : m_quackBehavior(move(quackBehavior))
{
    assert(m_quackBehavior);
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
    if (m_flyBehavior)
    {
        m_flyBehavior();
    }
}

void Duck::Dance()
{
    if (m_danceBehavior)
    {
        m_danceBehavior();
    }
}

void Duck::SetFlyBehavior(FlyBehavior flyBehavior)
{
    m_flyBehavior = flyBehavior;
}

void Duck::SetDanceBehavior(DanceBehavior danceBehavior)
{
    m_danceBehavior = danceBehavior;
}