#include "stdafx.h"
#include "InheritedCanvasAdapter.h"
#include <numeric>


InheritedCanvasAdapter::InheritedCanvasAdapter(std::ostream & strm)
    : modern_graphics_lib::CModernGraphicsRenderer(strm)
{
    BeginDraw();
}

void InheritedCanvasAdapter::MoveTo(int x, int y)
{
    m_currentPoint = { x, y };
}

void InheritedCanvasAdapter::LineTo(int x, int y)
{
    DrawLine(m_currentPoint, { x, y }, m_color);
}

void InheritedCanvasAdapter::SetColor(uint32_t rgbColor)
{
    static auto prepareColorValue = [](uint8_t colorValue) {
        static const auto maxColorComponentValue = std::numeric_limits<uint8_t>::max();
        return static_cast<float>(colorValue) / maxColorComponentValue;
    };

    uint8_t * color = reinterpret_cast<uint8_t*>(std::addressof(rgbColor));
    m_color.r = prepareColorValue(color[0]);
    m_color.g = prepareColorValue(color[1]);
    m_color.b = prepareColorValue(color[2]);
}