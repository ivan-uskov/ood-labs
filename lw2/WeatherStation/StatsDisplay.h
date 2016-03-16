#pragma once
#include "WeatherData.h"

class StatsDisplay : public WeatherData::ObserverType
{
public:
    void Update(WeatherInfo const& data) override;

    double m_minTemperature = std::numeric_limits<double>::infinity();
    double m_maxTemperature = -std::numeric_limits<double>::infinity();
    double m_accTemperature = 0;
    unsigned m_countAcc = 0;
};

