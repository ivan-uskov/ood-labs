#pragma once
#include "Shape.h"
#include "Point.h"

class CTriangle : public CShape
{
public:
    CTriangle(Color color, CPoint v1, CPoint v2, CPoint v3);

    CPoint const& GetV1() const;
    CPoint const& GetV2() const;
    CPoint const& GetV3() const;

    void Draw(ICanvas & canvas) override;
    void Accept(IShapeVisitor & visitor) const override;

private:
    CPoint m_v1;
    CPoint m_v2;
    CPoint m_v3;
};

