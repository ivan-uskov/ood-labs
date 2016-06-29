#include "stdafx.h"
#include "Shape.h"

CShape::CShape(Color color)
    : m_color(std::move(color))
{
}

Color CShape::GetColor() const
{
    return m_color;
}

void CShape::Draw(ICanvas & canvas)
{
    canvas.SetColor(GetColor());
}