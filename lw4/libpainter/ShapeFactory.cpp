#include "stdafx.h"
#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

using namespace std;

namespace
{
    bool ReadPoint(istream & in, CPoint & point)
    {
        return static_cast<bool>(in >> point.x >> point.y);
    }

    bool ReadColor(istream & in, Color & color)
    {
        string colorStr;
        in >> colorStr;

        map<string, Color> availableColors = {
            { "Green", Color::Green },
            { "Red", Color::Red },
            { "Blue", Color::Blue },
            { "Black", Color::Black },
            { "White", Color::White }
        };

        auto pos = availableColors.find(colorStr);
        if (pos != availableColors.end())
        {
            color = pos->second;
            return true;
        }

        return false;
    }

    unique_ptr<CShape> CreateRectangle(istream & dscStrm)
    {
        Color color;
        CPoint leftTop, rightBottom;
        if (ReadColor(dscStrm, color) && ReadPoint(dscStrm, leftTop) && ReadPoint(dscStrm, rightBottom))
        {
            return make_unique<CRectangle>(color, leftTop, rightBottom);
        }

        return unique_ptr<CShape>();
    }

    unique_ptr<CShape> CreateTriangle(istream & dscStrm)
    {
        Color color;
        CPoint v1, v2, v3;
        if (ReadColor(dscStrm, color) && ReadPoint(dscStrm, v1) && ReadPoint(dscStrm, v2) && ReadPoint(dscStrm, v3))
        {
            return make_unique<CTriangle>(color, v1, v2, v3);
        }

        return unique_ptr<CShape>();
    }

    unique_ptr<CShape> CreateEllipse(istream & dscStrm)
    {
        Color color;
        CPoint center;
        unsigned horizRadius, vertRadius;

        if (ReadColor(dscStrm, color) && ReadPoint(dscStrm, center) && (dscStrm >> horizRadius) && (dscStrm >> vertRadius))
        {
            return make_unique<CEllipse>(color, center, horizRadius, vertRadius);
        }

        return unique_ptr<CShape>();
    }

    unique_ptr<CShape> CreateRegularPolygon(istream & dscStrm)
    {
        Color color;
        CPoint center;
        unsigned radius, vertexCount;

        if (ReadColor(dscStrm, color) && ReadPoint(dscStrm, center) && (dscStrm >> radius) && (dscStrm >> vertexCount))
        {
            return make_unique<CRegularPolygon>(color, center, radius, vertexCount);
        }

        return unique_ptr<CShape>();
    }
}

unique_ptr<CShape> CShapeFactory::CreateShape(const string & description)
{
    istringstream in(description);
    string shapeName;
    in >> shapeName;

    map<string, function<unique_ptr<CShape>(istream&)>> availableShapes = {
        { "Rectangle", CreateRectangle },
        { "Triangle", CreateTriangle },
        { "Ellipse", CreateEllipse },
        { "RegularPolygon", CreateRegularPolygon }
    };

    auto pos = availableShapes.find(shapeName);
    if (pos != availableShapes.end())
    {
        return pos->second(in);
    }

    return unique_ptr<CShape>();
}