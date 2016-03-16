#pragma once
#include "Observer.h"

using namespace std;

struct WeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
};

class WeatherData : public Observable<WeatherInfo>
{
public:
    typedef ObserverType Display;

    // Температура в градусах Цельсия
    double GetTemperature() const;
    // Относительная влажность (0...100)
    double GetHumidity() const;
    // Атмосферное давление (в мм.рт.ст)
    double GetPressure() const;

    void MeasurementsChanged();

    void SetMeasurements(double temp, double humidity, double pressure);

protected:
    WeatherInfo GetChangedData() const override;

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};