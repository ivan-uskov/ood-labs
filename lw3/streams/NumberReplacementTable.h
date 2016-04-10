#pragma once

#include <map>
#include <random>
#include <algorithm>
#include <numeric>
#include <stdexcept>

template <typename T, typename RandomNumberGenerator = std::mt19937>
class CNumberReplacementTable
{
public:
    CNumberReplacementTable(unsigned seed)
        : m_table(GetTableSize())
        , m_reversedTable(GetTableSize())
        , m_min(std::numeric_limits<T>::min())
    {
        std::iota(m_table.begin(), m_table.end(), m_min);
        std::shuffle(m_table.begin(), m_table.end(), RandomNumberGenerator(seed));

        for (size_t i = 0; i < m_table.size(); ++i)
        {
            m_reversedTable[GetAbsoluteValue(m_table[i])] = GetRealValue(i);
        }
    }

    T replace(T item) const
    {
        return m_table.at(GetAbsoluteValue(item));
    }

    T unreplace(T item) const
    {
        return m_reversedTable.at(GetAbsoluteValue(item));
    }

private:
    T GetAbsoluteValue(T item) const
    {
        return item + std::abs(m_min);
    }

    T GetRealValue(size_t item) const
    {
        return static_cast<T>(item - std::abs(m_min));
    }

    size_t GetTableSize() const
    {
        static int BITS_IN_BYTE = 8;
        static int SS_BASE      = 2;
        return static_cast<size_t>(std::pow(SS_BASE, BITS_IN_BYTE * sizeof(T)));
    }

    T m_min;
    std::vector<T> m_table, m_reversedTable;
};