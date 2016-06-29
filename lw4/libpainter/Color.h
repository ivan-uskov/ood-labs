#pragma once

enum class Color
{
    Green,
    Red,
    Blue,
    Black,
    White
};

struct RGBColor
{
    unsigned r, g, b;

    RGBColor() = default;
    RGBColor(Color const& color)
    {
        switch (color)
        {
        case Color::Green:
            r = 0;
            g = 255;
            b = 0;
            break;
        case Color::Red:
            r = 255;
            g = 0;
            b = 0;
            break;
        case Color::Blue:
            r = 0;
            g = 0;
            b = 255;
            break;
        case Color::Black:
            r = 0;
            g = 0;
            b = 0;
            break;
        case Color::White:
            r = 255;
            g = 255;
            b = 255;
            break;
        }
    }
};