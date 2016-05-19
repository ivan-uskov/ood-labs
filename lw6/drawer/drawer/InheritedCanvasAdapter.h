#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class InheritedCanvasAdapter
    : public graphics_lib::ICanvas
    , protected modern_graphics_lib::CModernGraphicsRenderer
{
public:
    InheritedCanvasAdapter(std::ostream & strm);

    void MoveTo(int x, int y) override;
    void LineTo(int x, int y) override;
    void SetColor(uint32_t rgbColor) override;

private:
    modern_graphics_lib::CPoint m_currentPoint = {0, 0};
    modern_graphics_lib::CRGBAColor m_color = {0, 0, 0, 1};
};

