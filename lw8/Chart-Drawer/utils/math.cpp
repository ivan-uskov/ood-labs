#include "../stdafx.h"
#include "math.h"

namespace Math
{
    bool equals(double lhs, double rhs)
    {
          return fabs(lhs - rhs) < std::numeric_limits<double>::epsilon();
    }
}
