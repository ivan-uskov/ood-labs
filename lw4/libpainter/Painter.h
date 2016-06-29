#pragma once
#include "IShapeVisitor.h"
#include "ICanvas.h"
#include "IShape.h"

class CPainter : private IShapeVisitor
{
public:
    void Draw(std::shared_ptr<ICanvas> const& canvas, IShape & shape);

    void Visit(const CRectangle &) override;
    void Visit(const CTriangle &) override;
    void Visit(const CEllipse &) override;
    void Visit(const CRegularPolygon &) override;

private:
    std::shared_ptr<ICanvas> m_context;
};

