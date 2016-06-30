#pragma once
#include <QObject>
#include "iharmonicfactory.h"

class HarmonicFactory : public QObject, public IHarmonicFactory
{
    Q_OBJECT
public:
    std::shared_ptr<IHarmonic> Create(double amplitude, double frequency, double phase) override;
};
