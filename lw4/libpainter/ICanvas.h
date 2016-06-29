#pragma once

#include "Color.h"

struct CPoint;

class ICanvas
{
public:
    virtual void SetColor(Color const& color) = 0;
    virtual void DrawLine(CPoint const& from, CPoint const& to) = 0;
    virtual void DrawEllipse(CPoint const& center, unsigned horzRadius, unsigned vertRadius) = 0;

    virtual ~ICanvas() = default;
};