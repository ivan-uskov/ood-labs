#include "stdafx.h"
#include "PictureDraft.h"

using namespace std;

bool CPictureDraft::IsEmpty() const
{
    return m_shapes.empty();
}

CPictureDraft::ConstIterator CPictureDraft::begin() const
{
    return m_shapes.begin();
}

CPictureDraft::ConstIterator CPictureDraft::end() const
{
    return m_shapes.end();
}

void CPictureDraft::AddShape(unique_ptr<CShape> && shape)
{
    m_shapes.push_back(move(shape));
}

void CPictureDraft::Draw(ICanvas & canvas)
{
    for_each(m_shapes.begin(), m_shapes.end(), [&canvas](auto & shapePtr) {
        shapePtr->Draw(canvas);
    });
}

void CPictureDraft::Accept(IShapeVisitor & v) const
{
    for_each(m_shapes.begin(), m_shapes.end(), [&v](auto & shapePtr) {
        shapePtr->Accept(v);
    });
}