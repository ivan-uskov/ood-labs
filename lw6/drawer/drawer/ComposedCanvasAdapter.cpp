#include "stdafx.h"
#include "ComposedCanvasAdapter.h"
#include <numeric>

using namespace std;

ComposedCanvasAdapter::ComposedCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer && renderer)
    : m_renderer(move(renderer))
{
    try
    {
        m_renderer.BeginDraw();
    }
    catch (logic_error const&)
    {
        // Drawing has already begun
    }
}

void ComposedCanvasAdapter::MoveTo(int x, int y)
{
    m_currentPoint = {x, y};
}

void ComposedCanvasAdapter::LineTo(int x, int y)
{
    m_renderer.DrawLine(m_currentPoint, {x, y}, m_color);
}

void ComposedCanvasAdapter::SetColor(uint32_t rgbColor)
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