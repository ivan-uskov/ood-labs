#include "../stdafx.h"
#include "../utils/math.h"
#include "harmonic.h"
#include <QDebug>

Harmonic::Harmonic(double amplitude, double frequency, double phase, AngleFunction function)
    : m_amplitude(amplitude)
    , m_frequency(frequency)
    , m_function(function)
    , m_phase(phase)
{
    emit updated();
}

double Harmonic::operator () (double x) const
{
    return m_amplitude * m_function(m_frequency * x + m_phase);
}

QString Harmonic::getText() const
{
    return QString::number(m_amplitude) + " * " +
           QString(m_function) + "(" +
           QString::number(m_frequency) + " * x + " +
           QString::number(m_phase) + ")";
}

AngleFunction Harmonic::getFunction() const
{
    return m_function;
}

void Harmonic::setFunction(const AngleFunction & function)
{
    if (m_function != function)
    {
        m_function = function;
        emit updated();
    }
}

double Harmonic::getFrequency() const
{
    return m_frequency;
}

void Harmonic::setFrequency(double frequency)
{
    if (!Math::equals(m_frequency, frequency))
    {
        m_frequency = frequency;
        emit updated();
    }
}

double Harmonic::getAmplitude() const
{
    return m_amplitude;
}

void Harmonic::setAmplitude(double amplitude)
{
    if (!Math::equals(m_amplitude, amplitude))
    {
        m_amplitude = amplitude;
        emit updated();
    }
}

double Harmonic::getPhase() const
{
    return m_phase;
}

void Harmonic::setPhase(double phase)
{
    if (!Math::equals(m_phase, phase))
    {
        m_phase = phase;
        emit updated();
    }
}
