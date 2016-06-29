#pragma once

class CRectangle;
class CTriangle;
class CEllipse;
class CRegularPolygon;

class IShapeVisitor
{
public:
    virtual void Visit(const CRectangle &) = 0;
    virtual void Visit(const CTriangle &) = 0;
    virtual void Visit(const CEllipse &) = 0;
    virtual void Visit(const CRegularPolygon &) = 0;

    virtual ~IShapeVisitor() = default;
};