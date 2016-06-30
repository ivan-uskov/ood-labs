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

class IDecartesSpaceDrawable;

class HarmonicPlotItemsProvider : public QObject
{
    Q_OBJECT
public:
    typedef std::shared_ptr<IDecartesSpaceDrawable> Generator;

    HarmonicPlotItemsProvider(Math::Range const& xValues, double deltha);

    void setGenerator(Generator const& generator);

public slots:
    void regenerate();

signals:
    void regenerated(const HarmonicItems &);

private:
    Generator m_generator;
    HarmonicItems m_items;
};
