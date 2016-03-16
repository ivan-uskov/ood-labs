#pragma once
#include "WeatherData.h"

class Display : public WeatherData::Display
{
public:
    void Update(WeatherInfo const& data) override;
};
