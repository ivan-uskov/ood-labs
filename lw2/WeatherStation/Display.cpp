#include "stdafx.h"
#include "Display.h"

void Display::Update(WeatherInfo const& data)
{
    std::cout << "Current Temp " << data.temperature << std::endl;
    std::cout << "Current Hum " << data.humidity << std::endl;
    std::cout << "Current Pressure " << data.pressure << std::endl;
    std::cout << "----------------" << std::endl;
}