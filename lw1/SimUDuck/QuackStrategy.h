#pragma once

struct IQuackBehavior
{
    virtual ~IQuackBehavior() = default;
    virtual void Quack() = 0;
};

struct QuackBehavior : public IQuackBehavior
{
    void Quack() override;
};

struct SqueakBehavior : public IQuackBehavior
{
    void Quack() override;
};

struct MuteQuackBehavior : public IQuackBehavior
{
    void Quack() override {}
};