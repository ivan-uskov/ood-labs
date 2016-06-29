#pragma once
#include "Shape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
    CRectangle(Color color, CPoint leftTop, CPoint rightBottom);

    CPoint const& GetLeftTop() const;
    CPoint const& GetRightBottom() const;

    void Draw(ICanvas & canvas) override;

    void Accept(IShapeVisitor & visitor) const override;

private:
    CPoint m_leftTop;
    CPoint m_rightBottom;
};

