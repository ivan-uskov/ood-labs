#include "stdafx.h"
#include "SvgCanvas.h"

#include <boost/format.hpp>

using namespace std;

void CSvgCanvas::Flush(const std::string & fileName) const
{
    ofstream(fileName) << (boost::format(R"(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg version="1.1" width="300px" height="234.494px" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px">%1%</svg>
)") % m_canvas).str();
}

void CSvgCanvas::Clear()
{
    m_canvas.clear();
}

void CSvgCanvas::SetColor(Color const& color)
{
    m_currentColor = RGBColor(color);
}

void CSvgCanvas::DrawLine(CPoint const& from, CPoint const& to)
{
    UpdateBoundingBox(from);
    UpdateBoundingBox(to);
    AddLine((boost::format(R"(<line x1="%1%" y1="%2%" x2="%3%" y2="%4%" style="stroke:rgb(%5%, %6%, %7%);stroke-width:2" />)")
        % from.x
        % from.y
        % to.x
        % to.y
        % m_currentColor.r
        % m_currentColor.g
        % m_currentColor.b
    ).str());
}

void CSvgCanvas::DrawEllipse(CPoint const& center, unsigned horzRadius, unsigned vertRadius)
{
    CPoint rightBottom = {center.x + horzRadius, center.y + vertRadius};
    UpdateBoundingBox(rightBottom);
    AddLine((boost::format(R"(<ellipse cx="%1%" cy="%2%" rx="%3%" ry="%4%" style="fill:white;stroke:rgb(%5%, %6%, %7%);stroke-width:2" />)")
        % center.x
        % center.y
        % horzRadius
        % vertRadius
        % m_currentColor.r
        % m_currentColor.g
        % m_currentColor.b
    ).str());
}

void CSvgCanvas::AddLine(const std::string & line)
{
    m_canvas += "  " + line + "\n";
}

void CSvgCanvas::UpdateBoundingBox(CPoint const& point)
{
    if (point.x > m_boundBoxRightBottom.x)
    {
        m_boundBoxRightBottom.x = point.x;
    }

    if (point.y > m_boundBoxRightBottom.y)
    {
        m_boundBoxRightBottom.y = point.y;
    }
}