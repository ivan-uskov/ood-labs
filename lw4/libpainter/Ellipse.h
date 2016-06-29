#pragma once
#include "Shape.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
    CEllipse(Color color, CPoint center, unsigned horizRadius, unsigned vertRadius);

    CPoint const& GetCenter() const;
    unsigned GetHorizontalRadius() const;
    unsigned GetVerticalRadius() const;

    void Draw(ICanvas & canvas) override;
    void Accept(IShapeVisitor & visitor) const override;

private:
    CPoint m_center;
    unsigned m_horizRadius;
    unsigned m_vertRadius;
};

