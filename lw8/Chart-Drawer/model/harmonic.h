#pragma once
#include <QObject>
#include "iharmonic.h"

class Harmonic : public IHarmonic
{
    Q_OBJECT
public:
    Harmonic() = default;
    Harmonic(double m_amplitude, double m_frequency, double m_phase, AngleFunction m_function = AngleFunction());

    double operator () (double x) const override;
    QString getText() const override;

    AngleFunction getFunction() const override;
    double getPhase() const override;
    double getFrequency() const override;
    double getAmplitude() const override;

public slots:
    void setFunction(const AngleFunction & funcation) override;
    void setFrequency(double frequency) override;
    void setAmplitude(double amplitude) override;
    void setPhase(double phase) override;

private:
    double m_phase     = 0.0f;
    double m_amplitude = 1.0f;
    double m_frequency = 1.0f;
    AngleFunction m_function;
};
