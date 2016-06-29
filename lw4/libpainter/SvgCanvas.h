#pragma once
#include "ICanvas.h"
#include "Point.h"

class CSvgCanvas : public ICanvas
{
public:
    void SetColor(Color const& color) override;
    void DrawLine(CPoint const& from, CPoint const& to) override;
    void DrawEllipse(CPoint const& center, unsigned horzRadius, unsigned vertRadius) override;

    void Flush(const std::string &fileName) const;
    void Clear();

private:
    void UpdateBoundingBox(CPoint const& point);
    void AddLine(const std::string & line);

    RGBColor m_currentColor = Color::Black;
    CPoint m_boundBoxRightBottom = {0, 0};

    std::string m_canvas;
};

