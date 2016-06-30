#include "../stdafx.h"
#include "anglefunction.h"
#include <QString>

namespace
{
    QString const COS_STR = "Cos";
    QString const SIN_STR = "Sin";
}

AngleFunction::AngleFunction(const QString & functionStr)
{
    if (functionStr == COS_STR)
    {
        m_type = Type::Cos;
    }
    else if (functionStr == SIN_STR)
    {
        m_type = Type::Sin;
    }
    else
    {
        m_type = Type::Invalid;
    }
}

AngleFunction::operator QString () const
{
    switch (m_type)
    {
    case Type::Cos:
        return COS_STR;
    case Type::Sin:
        return SIN_STR;
    default:
        return "";
    }
}

double AngleFunction::operator () (double angle) const
{
    switch (m_type)
    {
    case Type::Cos:
        return cos(angle);
    case Type::Sin:
        return sin(angle);
    default:
        return 0.0;
    }
}

bool AngleFunction::isValid() const
{
    return m_type != Type::Invalid;
}

bool AngleFunction::operator != (const AngleFunction & func) const
{
    return m_type != func.m_type;
}

