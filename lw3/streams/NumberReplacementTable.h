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
        , m_min(std::numeric_limits<T>::min())
    {
        std::iota(m_table.begin(), m_table.end(), m_min);
        std::shuffle(m_table.begin(), m_table.end(), RandomNumberGenerator(seed));
    }

    T replace(T const& item) const
    {
        return m_table.at(item + std::abs(m_min));
    }

    T unreplace(T const& item) const
    {
        auto it = std::find(m_table.begin(), m_table.end(), item);
        if (it == m_table.end())
        {
            throw std::out_of_range("Unexpected value");
        }

        return (it - m_table.begin()) + m_min;
    }

private:

    size_t GetTableSize() const
    {
        static int BITS_IN_BYTE = 8;
        static int SS_BASE      = 2;
        return static_cast<size_t>(std::pow(SS_BASE, BITS_IN_BYTE * sizeof(T)));
    }

    T m_min;
    std::vector<T> m_table;
};