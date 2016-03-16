#pragma once
#include "WeatherData.h"

class Display : public WeatherData::ObserverType
{
public:
    void Update(WeatherInfo const& data) override;
};
