#include "stdafx.h"
#include "RegularPolygon.h"

using namespace std;

CRegularPolygon::CRegularPolygon(Color color, CPoint center, unsigned radius, unsigned vertexCount)
    : CShape(color)
    , m_center(center)
    , m_radius(radius)
    , m_vertexCount(vertexCount)
{}

CPoint const& CRegularPolygon::GetCenter() const
{
    return m_center;
}

unsigned CRegularPolygon::GetRadius() const
{
    return m_radius;
}

unsigned CRegularPolygon::GetVertexCount() const
{
    return m_vertexCount;
}

void CRegularPolygon::Draw(ICanvas & canvas)
{
    CShape::Draw(canvas);

    auto points = GetBoundingPoints();
    if (points.size())
    {
        auto nextIt = points.begin();
        auto current = *nextIt;
        while (++nextIt != points.end())
        {
            canvas.DrawLine(current, *nextIt);
            current = *nextIt;
        }
    }
}

void CRegularPolygon::Accept(IShapeVisitor & visitor) const
{
    visitor.Visit(*this);
}

vector<CPoint> CRegularPolygon::GetBoundingPoints() const
{
    auto angle = M_PI * 2 / m_vertexCount;
    vector<CPoint> points;
    unsigned notCalculatedPoints = m_vertexCount;
    do
    {
        points.push_back({
            unsigned(m_center.x + m_radius * cos(angle * notCalculatedPoints)),
            unsigned(m_center.y + m_radius * sin(angle * notCalculatedPoints))
        });
    }
    while (notCalculatedPoints--);

    return points;
}
