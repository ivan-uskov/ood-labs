#include "stdafx.h"
#include "Painter.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

using namespace std;

void CPainter::Draw(std::shared_ptr<ICanvas> const& canvas, IShape & shape)
{
    if (canvas)
    {
        m_context = canvas;
        shape.Accept(*this);
        m_context.reset();
    }
}

void CPainter::Visit(const CRectangle & rect)
{
    auto leftTop = rect.GetLeftTop();
    auto rightBottom = rect.GetRightBottom();
    m_context->SetColor(rect.GetColor());

    m_context->DrawLine(leftTop, { rightBottom.x, leftTop.y });
    m_context->DrawLine({ rightBottom.x, leftTop.y }, rightBottom);
    m_context->DrawLine(rightBottom, { leftTop.x, rightBottom.y });
    m_context->DrawLine({ leftTop.x, rightBottom.y }, leftTop);
}

void CPainter::Visit(const CTriangle & tr)
{
    auto v1 = tr.GetV1();
    auto v2 = tr.GetV2();
    auto v3 = tr.GetV3();
    m_context->SetColor(tr.GetColor());

    m_context->DrawLine(v1, v2);
    m_context->DrawLine(v2, v3);
    m_context->DrawLine(v3, v1);
}

void CPainter::Visit(const CEllipse & ell)
{
    m_context->SetColor(ell.GetColor());
    m_context->DrawEllipse(ell.GetCenter(), ell.GetHorizontalRadius(), ell.GetVerticalRadius());
}

void CPainter::Visit(const CRegularPolygon & rr)
{
    m_context->SetColor(rr.GetColor());

    auto points = rr.GetBoundingPoints();
    if (points.size())
    {
        auto nextIt = points.begin();
        auto current = *nextIt;
        while (++nextIt != points.end())
        {
            m_context->DrawLine(current, *nextIt);
            current = *nextIt;
        }
    }
}
