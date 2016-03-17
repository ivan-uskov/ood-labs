#pragma once

template <typename T>
class SimpleStatisticsCalculator
{
public:
    void Update(T const& newValue)
    {
        if (m_minValue > newValue)
        {
            m_minValue = newValue;
        }
        if (m_maxValue < newValue)
        {
            m_maxValue = newValue;
        }

        m_accValue += newValue;
        ++m_countAcc;
    }

    T GetMax() const
    {
        return m_maxValue;
    }

    T GetMin() const
    {
        return m_minValue;
    }

    T GetAvórage() const
    {
        return m_accValue / m_countAcc;
    }

private:
    T m_minValue = std::numeric_limits<T>::infinity();
    T m_maxValue = -std::numeric_limits<T>::infinity();
    T m_accValue = 0;
    size_t m_countAcc = 0;
};

