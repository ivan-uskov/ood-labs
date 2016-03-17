#include "stdafx.h"
#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"

using namespace std;

int main()
{
    WeatherData wd;

    auto display = make_shared<Display>();
    wd.RegisterObserver(display);

    auto statsDisplay = make_shared<StatsDisplay>();
    wd.RegisterObserver(statsDisplay);

    wd.SetMeasurements(3, 0.7, 760);
    wd.SetMeasurements(4, 0.8, 761);

    wd.RemoveObserver(statsDisplay);

    wd.SetMeasurements(10, 0.8, 761);
    wd.SetMeasurements(-10, 0.8, 761);
    return 0;
}