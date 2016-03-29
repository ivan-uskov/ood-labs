#include "stdafx.h"
#include "StatsDisplay.h"
#include "WeatherStationType.h"

using namespace std;

void StatsDisplay::Update(ObservableType const& subject)
{
    UpdateStatistics(subject.GetChangedData());
    PrintWeatherStationInfo(subject.GetObservableId());
    PrintStatistics();
}

void StatsDisplay::UpdateStatistics(WeatherInfo const& data)
{
    m_humidityStats.Update(data.humidity);
    m_pressureStats.Update(data.pressure);
    m_temperatureStats.Update(data.temperature);
}

void StatsDisplay::PrintWeatherStationInfo(size_t weatherStationId) const
{
    if (IsWeatherStationType(weatherStationId))
    {
        cout << "WeatherStation type: " << static_cast<WeatherStationType>(weatherStationId) << endl;
    }
}

void StatsDisplay::PrintStatistics() const
{
    PrintParameterStatistics(m_humidityStats, "Humidity");
    PrintParameterStatistics(m_pressureStats, "Pressure");
    PrintParameterStatistics(m_temperatureStats, "Temperature");
}

void StatsDisplay::PrintParameterStatistics(ParameterStats const& stats, string const& parameterName) const
{
    cout << "Max " << parameterName << " " << stats.GetMax() << endl;
    cout << "Min " << parameterName << " " << stats.GetMin() << endl;
    cout << "Average " << parameterName << " " << stats.GetAvórage() << endl;
    cout << "----------------" << endl;
}