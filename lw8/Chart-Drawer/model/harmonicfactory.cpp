#include "stdafx.h"
#include "harmonicfactory.h"
#include "harmonic.h"

std::shared_ptr<IHarmonic> HarmonicFactory::Create(double amplitude, double frequency, double phase)
{
    return make_shared<Harmonic>(amplitude, frequency, phase);
}
