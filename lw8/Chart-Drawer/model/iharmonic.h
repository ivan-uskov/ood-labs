#pragma once
#include "anglefunction.h"
#include "idecartesspacedrawable.h"
#include <QString>
#include <QObject>

class IHarmonic : public QObject, public IDecartesSpaceDrawable
{
    Q_OBJECT
public:
    virtual QString getText() const = 0;

    virtual AngleFunction getFunction() const = 0;
    virtual double getFrequency() const = 0;
    virtual double getAmplitude() const = 0;
    virtual double getPhase() const = 0;

public slots:
    virtual void setFunction(const AngleFunction & function) = 0;
    virtual void setFrequency(double frequency) = 0;
    virtual void setAmplitude(double amplitude) = 0;
    virtual void setPhase(double phase) = 0;

signals:
    void updated();
};
