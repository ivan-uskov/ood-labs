#pragma once
#include <functional>

typedef std::function<void()> FlyBehavior;

class FlyWithWings
{
public:
    void operator () ();

private:
    size_t m_flyCounter = 0;
};
