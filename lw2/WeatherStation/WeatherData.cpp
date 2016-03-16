#include "stdafx.h"
#include "WeatherData.h"

double WeatherData::GetTemperature() const
{
    return m_temperature;
}

// ������������� ��������� (0...100)
double WeatherData::GetHumidity() const
{
    return m_humidity;
}

// ����������� �������� (� ��.��.��)
double WeatherData::GetPressure() const
{
    return m_pressure;
}

void WeatherData::MeasurementsChanged()
{
    NotifyObservers();
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure)
{
    m_humidity    = humidity;
    m_pressure    = pressure;
    m_temperature = temp;

    MeasurementsChanged();
}

WeatherInfo WeatherData::GetChangedData() const
{
    WeatherInfo info;
    info.temperature = GetTemperature();
    info.humidity = GetHumidity();
    info.pressure = GetPressure();
    return info;
}