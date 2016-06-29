#pragma once
#include <memory>
#include <vector>
#include <boost/iterator/indirect_iterator.hpp>
#include "Shape.h"

class CPictureDraft : public IShape
{
public:
    typedef std::vector<std::unique_ptr<CShape>> Storage;
    typedef boost::indirect_iterator<Storage::const_iterator, const CShape&> ConstIterator;

    CPictureDraft() = default;

    void Draw(ICanvas & canvas) override;
    void Accept(IShapeVisitor & v) const override;

    bool IsEmpty() const;

    ConstIterator begin() const;
    ConstIterator end() const;

    void AddShape(std::unique_ptr<CShape> && shape);

    CPictureDraft(CPictureDraft &&) = default;
    CPictureDraft & operator=(CPictureDraft &&) = default;

    CPictureDraft(const CPictureDraft &) = delete;
    CPictureDraft & operator=(const CPictureDraft &) = delete;
private:
    Storage m_shapes;
};

inline CPictureDraft::ConstIterator begin(const CPictureDraft & draft)
{
    return draft.begin();
}

inline CPictureDraft::ConstIterator end(const CPictureDraft & draft)
{
    return draft.end();
}
