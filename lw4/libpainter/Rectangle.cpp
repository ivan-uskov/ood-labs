#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(Color color, CPoint leftTop, CPoint rightBottom)
    : CShape(move(color))
    , m_leftTop(move(leftTop))
    , m_rightBottom(move(rightBottom))
{}

CPoint const& CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

CPoint const& CRectangle::GetRightBottom() const
{
    return m_rightBottom;
}

void CRectangle::Draw(ICanvas & canvas)
{
    CShape::Draw(canvas);

    canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
    canvas.DrawLine({ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
    canvas.DrawLine(m_rightBottom, { m_leftTop.x, m_rightBottom.y });
    canvas.DrawLine({ m_leftTop.x, m_rightBottom.y }, m_leftTop);
}

void CRectangle::Accept(IShapeVisitor & visitor) const
{
    visitor.Visit(*this);
}