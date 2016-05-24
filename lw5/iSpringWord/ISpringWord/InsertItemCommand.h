#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <boost/optional.hpp>

template <typename RandomAccessCollection>
class CInsertItemCommand : public CAbstractCommand
{
public:
    CInsertItemCommand(
        RandomAccessCollection & collection, 
        typename RandomAccessCollection::value_type item, 
        boost::optional<size_t> const& position
    )
        : m_collection(collection)
        , m_itemToBeInserted(move(item))
        , m_position(position)
    {}

    void DoExecute() override
    {
        if (m_position == boost::none)
        {
            m_collection.push_back(m_itemToBeInserted);
        }
        else
        {
            auto pos = m_collection.begin() + (*m_position);
            m_collection.insert(pos, m_itemToBeInserted);
        }
    }

    void DoUnexecute() override
    {
        auto pos = m_position != boost::none ? m_collection.begin() + *m_position : --m_collection.end();
        m_collection.erase(pos);
    }

private:
    RandomAccessCollection & m_collection;
    typename RandomAccessCollection::value_type m_itemToBeInserted;
    boost::optional<size_t> m_position;
};

