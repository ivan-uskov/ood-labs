#pragma once;

namespace Math
{
    class Range
    {
    public:
        Range() = default;
        Range(double from, double to);

        bool isValid() const;

        double from() const;
        double to() const;

    private:
        double m_from;
        double m_to;
    };
}
