#pragma once
#include <memory>

class IHarmonic;

class IHarmonicFactory
{
public:
    virtual std::shared_ptr<IHarmonic> Create(double amplitude, double frequency, double phase) = 0;
    virtual ~IHarmonicFactory() = default;
};
