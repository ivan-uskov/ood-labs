#pragma once
#include "IShapeFactory.h"

struct CPoint;
enum class Color;

class CShapeFactory : public IShapeFactory
{
public:
    std::unique_ptr<CShape> CreateShape(const std::string & description) override;
};

