#include "stdafx.h"
#include "Triangle.h"

using namespace std;

CTriangle::CTriangle(Color color, CPoint v1, CPoint v2, CPoint v3)
    : CShape(move(color))
    , m_v1(v1)
    , m_v2(v2)
    , m_v3(v3)
{}

CPoint const& CTriangle::GetV1() const
{
    return m_v1;
}

CPoint const& CTriangle::GetV2() const
{
    return m_v2;
}

CPoint const& CTriangle::GetV3() const
{
    return m_v3;
}

void CTriangle::Draw(ICanvas & canvas)
{
    CShape::Draw(canvas);

    canvas.DrawLine(m_v1, m_v2);
    canvas.DrawLine(m_v2, m_v3);
    canvas.DrawLine(m_v3, m_v1);
}

void CTriangle::Accept(IShapeVisitor & visitor) const
{
    visitor.Visit(*this);
}
