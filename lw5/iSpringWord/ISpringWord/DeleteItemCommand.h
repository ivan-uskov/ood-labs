#pragma once
#include "AbstractCommand.h"

template <typename RandomAccessCollection>
class CDeleteItemCommand : public CAbstractCommand
{
public:
    CDeleteItemCommand(RandomAccessCollection & collection, size_t position)
        : m_collection(collection)
        , m_position(position)
    {}

    void DoExecute() override
    {
        auto pos = m_collection.begin() + m_position;
        m_itemToBeDeleted = *pos;
        m_collection.erase(pos);
    }

    void DoUnexecute() override
    {
        auto pos = m_collection.begin() + m_position;
        m_collection.insert(pos, m_itemToBeDeleted);
    }

private:
    RandomAccessCollection & m_collection;
    typename RandomAccessCollection::value_type m_itemToBeDeleted;
    size_t m_position;
};

