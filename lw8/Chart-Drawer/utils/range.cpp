#include "../stdafx.h"
#include "range.h"

namespace Math
{
    Range::Range(double from, double to)
        : m_from(from)
        , m_to(to)
    {
    }

    bool Range::isValid() const
    {
        return m_from <= m_to;
    }

    double Range::from() const
    {
        return m_from;
    }

    double Range::to() const
    {
        return m_to;
    }
}
