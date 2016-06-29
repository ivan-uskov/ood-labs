#include "stdafx.h"
#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"

using namespace std;

CDesigner::CDesigner(IShapeFactory & factory)
    :m_factory(factory)
{
}

CPictureDraft CDesigner::CreateDraft(std::istream & inputData)
{
    CPictureDraft draft;
    string line;
    while (getline(inputData, line))
    {
        auto shape = m_factory.CreateShape(line);
        if (shape != nullptr)
        {
            draft.AddShape(move(shape));
        }
    }
    return draft;
}
