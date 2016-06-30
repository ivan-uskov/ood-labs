#pragma once

class IDecartesSpaceDrawable
{
public:
    virtual double operator () (double x) const = 0;
    virtual ~IDecartesSpaceDrawable() = default;
};
