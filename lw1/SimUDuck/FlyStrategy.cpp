#include "stdafx.h"
#include "FlyStrategy.h"

using namespace std;

namespace FlyStrategy
{
    void FlyWithWings::operator () ()
    {
        cout << "My fly Impl " << ++m_flyCounter << endl;
    }
}
