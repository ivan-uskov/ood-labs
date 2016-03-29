#pragma once
#include <iostream>

enum class WeatherStationType
{
    In  = 1,
    Out = 2
};

std::ostream & operator << (std::ostream & out, WeatherStationType const& type);
bool IsWeatherStationType(size_t type);