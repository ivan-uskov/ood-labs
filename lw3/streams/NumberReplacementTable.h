#pragma once

#include <map>
#include <random>
#include <algorithm>

template <typename T, typename RandomNumberGenerator = std::mt19937>
class CNumberReplacementTable
{
public:
    CNumberReplacementTable(unsigned seed)
        : m_map()
    {
        for (T i = std::numeric_limits<T>::min(); i <= std::numeric_limits<T>::max(); ++i)
        {
            m_map[i] = i;
        }
        std::shuffle(m_map.begin(), m_map.end(), RandomNumberGenerator(seed));
    }

    T replace(T const& item)
    {
        return m_map.at(item);
    }

private:
    struct ReplacementRow
    {
        T from, to;
    };

    std::map<T, T> m_map;

};