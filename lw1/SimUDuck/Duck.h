#pragma once
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"

typedef std::function<void()> QuackBehavior;
typedef std::function<void()> DanceBehavior;
typedef std::function<void()> FlyBehavior;

class Duck
{
public:
    void Quack() const;
    void Swim();
    void Fly();
    void Dance();
    virtual void Display() const = 0;

    void SetFlyBehavior(FlyBehavior flyBehavior);
    void SetDanceBehavior(DanceBehavior danceBehavior);
    void SetQuackBehavior(QuackBehavior danceBehavior);

    virtual ~Duck() = default;

private:
    FlyBehavior m_flyBehavior;
    QuackBehavior m_quackBehavior;
    DanceBehavior m_danceBehavior;
};