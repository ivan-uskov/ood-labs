#include "stdafx.h"
#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"
#include "WeatherStationType.h"

using namespace std;

void WeatherStation()
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
}

void WeatherStationDuo()
{
    WeatherData wdIn, wdOut;

    wdIn.SetObservableId(static_cast<size_t>(WeatherStationType::In));
    wdOut.SetObservableId(static_cast<size_t>(WeatherStationType::Out));

    auto statsDisplay = make_shared<StatsDisplay>();
    wdIn.RegisterObserver(statsDisplay);
    wdOut.RegisterObserver(statsDisplay);


    wdIn.SetMeasurements(3, 0.7, 760);
    wdOut.SetMeasurements(4, 0.8, 761);
}

int main()
{
    WeatherStation();
    WeatherStationDuo();
    return 0;
}