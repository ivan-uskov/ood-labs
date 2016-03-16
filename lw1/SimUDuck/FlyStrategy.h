#pragma once

namespace FlyStrategy
{
    class FlyWithWings
    {
    public:
        void operator () ();

    private:
        size_t m_flyCounter = 0;
    };

}
