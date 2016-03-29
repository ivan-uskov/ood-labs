#include "stdafx.h"
#include "WeatherStationType.h"

std::ostream & operator << (std::ostream & out, WeatherStationType const& type)
{
    switch (type)
    {
    case WeatherStationType::In:
        out << "In weather station" << std::endl;
    case WeatherStationType::Out:
        out << "Out weather station" << std::endl;
    }

    return out;
}

bool IsWeatherStationType(size_t type)
{
    return type == static_cast<size_t>(WeatherStationType::In) ||
           type == static_cast<size_t>(WeatherStationType::Out);
}