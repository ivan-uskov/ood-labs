#pragma once
#include "WeatherData.h"
#include "SimpleStatisticsCalculator.h"

class StatsDisplay : public WeatherData::Display
{
public:
    void Update(ObservableType const& subject) override;

private:
    typedef SimpleStatisticsCalculator<double> ParameterStats;

    void UpdateStatistics(WeatherInfo const& data);
    void PrintStatistics() const;
    void PrintWeatherStationInfo(size_t weatherStationId) const;

    void PrintParameterStatistics(ParameterStats const& stats, std::string const& parameterName) const;

    ParameterStats m_pressureStats;
    ParameterStats m_humidityStats;
    ParameterStats m_temperatureStats;
};

