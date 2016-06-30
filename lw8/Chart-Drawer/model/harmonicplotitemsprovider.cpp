#include "../stdafx.h"
#include "harmonicplotitemsprovider.h"
#include "iharmonic.h"

using namespace Math;

HarmonicPlotItemsProvider::HarmonicPlotItemsProvider(Range const& xValues, double deltha)
{
     m_items.xRange = xValues;
     m_items.deltha = deltha;
}

void HarmonicPlotItemsProvider::regenerate()
{
    m_items.xs.clear();
    m_items.ys.clear();
    double minY = (*m_generator)(m_items.xRange.from());
    double maxY = (*m_generator)(m_items.xRange.to());

    if (m_generator)
    {
        for (auto i = m_items.xRange.from(); i <= m_items.xRange.to(); i += m_items.deltha)
        {
            m_items.xs.push_back(i);
            double yVal = (*m_generator)(i);
            m_items.ys.push_back(yVal);

            if (yVal < minY)
            {
                minY = yVal;
            }
            if (yVal > maxY)
            {
                maxY = yVal;
            }
        }
    }

    m_items.yRange = Range(minY, maxY);

    emit regenerated(m_items);
}

void HarmonicPlotItemsProvider::setGenerator(Generator const& generator)
{
    m_generator = generator;
    regenerate();
}
