#pragma once
#include "FlyStrategy.h"
#include "QuackStrategy.h"
#include "DanceStrategy.h"

class Duck
{
public:
    Duck(std::unique_ptr<IFlyBehavior> && flyBehavior, std::unique_ptr<IQuackBehavior> && quackBehavior);

    void Quack() const;
    void Swim();
    void Fly();
    virtual void Dance();
    virtual void Display() const = 0;

    void SetFlyBehavior(std::unique_ptr<IFlyBehavior> && flyBehavior);
    void SetDanceBehavior(DanceBehavior danceBehavior);

    virtual ~Duck() = default;

private:
    std::unique_ptr<IFlyBehavior> m_flyBehavior;
    std::unique_ptr<IQuackBehavior> m_quackBehavior;
    DanceBehavior m_danceBehavior;
};