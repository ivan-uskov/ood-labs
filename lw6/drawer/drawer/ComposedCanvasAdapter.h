#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ComposedCanvasAdapter : public graphics_lib::ICanvas
{
public:
    ComposedCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer && m_renderer);

    void MoveTo(int x, int y) override;
    void LineTo(int x, int y) override;
    void SetColor(uint32_t rgbColor) override;

private:
    modern_graphics_lib::CPoint m_currentPoint = {0, 0};
    modern_graphics_lib::CRGBAColor m_color = {0, 0, 0, 1};
    modern_graphics_lib::CModernGraphicsRenderer m_renderer;
};
