#pragma once
#include "WeatherData.h"

class Display : public WeatherData::Display
{
public:
    void Update(ObservableType const& subject) override;
};
