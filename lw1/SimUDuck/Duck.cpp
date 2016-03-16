#include "stdafx.h"
#include "Duck.h"

using namespace std;

void Duck::Quack() const
{
    if (m_quackBehavior)
    {
        m_quackBehavior();
    }
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

void Duck::SetQuackBehavior(QuackBehavior danceBehavior)
{
    m_quackBehavior = danceBehavior;
}