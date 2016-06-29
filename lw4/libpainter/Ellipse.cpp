#include "stdafx.h"
#include "Ellipse.h"

using namespace std;

CEllipse::CEllipse(Color color, CPoint center, unsigned horizRadius, unsigned vertRadius)
    : CShape(move(color))
    , m_center(move(center))
    , m_horizRadius(horizRadius)
    , m_vertRadius(vertRadius)
{}


CPoint const& CEllipse::GetCenter() const
{
    return m_center;
}

unsigned CEllipse::GetHorizontalRadius() const
{
    return m_horizRadius;
}

unsigned CEllipse::GetVerticalRadius() const
{
    return m_vertRadius;
}

void CEllipse::Draw(ICanvas & canvas)
{
    CShape::Draw(canvas);
    canvas.DrawEllipse(m_center, m_horizRadius, m_vertRadius);
}

void CEllipse::Accept(IShapeVisitor & visitor) const
{
    visitor.Visit(*this);
}