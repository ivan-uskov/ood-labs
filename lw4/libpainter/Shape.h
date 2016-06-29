#pragma once

#include "Color.h"
#include "ICanvas.h"
#include "IShape.h"

class CShape : public IShape
{
public:
    virtual ~CShape() = default;

    Color GetColor() const;

    void Draw(ICanvas & canvas) override;

protected:
    CShape(Color color);

private:
    Color m_color;
};