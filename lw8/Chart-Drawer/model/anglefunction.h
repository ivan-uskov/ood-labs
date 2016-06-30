#pragma once

class QString;

class AngleFunction
{
public:
    AngleFunction() = default;
    AngleFunction(const QString & functionStr);

    operator QString () const;
    double operator () (double angle) const;
    bool operator != (const AngleFunction & func) const;
    bool isValid() const;

private:
    enum class Type
    {
        Sin,
        Cos,
        Invalid
    };

    Type m_type = Type::Sin;
};
