#pragma once

#include "ICanvas.h"
#include "IShapeVisitor.h"

class IShape
{
public:

    virtual void Draw(ICanvas & canvas) = 0;
    virtual void Accept(IShapeVisitor & v) const = 0;

    virtual ~IShape() = default;
};
