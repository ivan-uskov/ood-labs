#pragma once
#include <QObject>
#include <QVector>
#include <functional>
#include <memory>
#include "../utils/range.h"

struct HarmonicItems
{
    Math::Range xRange;
    Math::Range yRange;
    QVector<double> xs, ys;
    double deltha;
};

class IHarmonic;

class HarmonicPlotItemsProvider : public QObject
{
    Q_OBJECT
public:
    typedef std::shared_ptr<IHarmonic> Generator;

    HarmonicPlotItemsProvider(Math::Range const& xValues, double deltha);

    void setGenerator(Generator const& generator);

signals:
    void regenerated(const HarmonicItems &);

private:
    void regenerate();

    Generator m_generator;
    HarmonicItems m_items;
};
