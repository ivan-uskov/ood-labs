#include "VectorMemoryStream.h"
#include <stdexcept>

using namespace std;

size_t CVectorMemoryStream::Size() const
{
    return m_memory.size();
}

uint8_t & CVectorMemoryStream::operator [] (size_t idx)
{
    if (idx >= Size())
    {
        throw out_of_range("Invalid index!");
    }

    return m_memory[idx];
}

uint8_t const& CVectorMemoryStream::operator [] (size_t idx) const
{
    return (*this)[idx];
}

void CVectorMemoryStream::Add(uint8_t const& value)
{
    m_memory.push_back(value);
}

void CVectorMemoryStream::Remove(size_t idx)
{
    auto it = m_memory.begin() + idx;
    if (it >= m_memory.end())
    {
        throw out_of_range("Unexpected index!");
    }

    m_memory.erase(it);
}