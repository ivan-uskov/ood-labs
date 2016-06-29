#pragma once
#include "Shape.h"
#include "Point.h"

class CRegularPolygon : public CShape
{
public:
    CRegularPolygon(Color color, CPoint center, unsigned radius, unsigned vertexCount);

    CPoint const& GetCenter() const;
    unsigned GetRadius() const;
    unsigned GetVertexCount() const;
    std::vector<CPoint> GetBoundingPoints() const;

    void Draw(ICanvas & canvas) override;
    void Accept(IShapeVisitor & visitor) const override;

private:
    const CPoint m_center;
    const unsigned m_radius;
    const unsigned m_vertexCount;
};