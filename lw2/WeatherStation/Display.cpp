#include "stdafx.h"
#include "Display.h"

void Display::Update(ObservableType const& subject)
{
    auto data = subject.GetChangedData();
    std::cout << "Current Temp " << data.temperature << std::endl;
    std::cout << "Current Hum " << data.humidity << std::endl;
    std::cout << "Current Pressure " << data.pressure << std::endl;
    std::cout << "----------------" << std::endl;
}