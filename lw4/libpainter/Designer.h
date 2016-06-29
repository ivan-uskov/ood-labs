#pragma once
#include <iosfwd>

#include "PictureDraft.h"

struct IShapeFactory;

class CDesigner
{
public:
    CDesigner(IShapeFactory & factory);
    CPictureDraft CreateDraft(std::istream & inputData);
private:
    IShapeFactory & m_factory;
};

