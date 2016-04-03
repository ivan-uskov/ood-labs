#include "MemoryInputStream.h"

using namespace std;

CMemoryInputStream::CMemoryInputStream(IMemoryStream<uint8_t> & memoryStream)
    : m_memoryStream(memoryStream)
{}

bool CMemoryInputStream::IsEOF() const
{
    return m_offset >= m_memoryStream.Size();
}

uint8_t CMemoryInputStream::ReadByte()
{
    uint8_t data;
    ReadBlock(&data, 1);
    return data;
}

streamsize CMemoryInputStream::ReadBlock(void * dstBuffer, streamsize size)
{
    if (!HasUnreadData(size))
    {
        throw out_of_range("Can't read data more than exists!");
    }

    auto bufferPtr = reinterpret_cast<uint8_t*>(dstBuffer);
    for (size_t i = 0; i < size; ++i)
    {
        *(bufferPtr++) = m_memoryStream[m_offset++];
    }

    return size;
}

bool CMemoryInputStream::HasUnreadData(size_t size) const
{
    return size + m_offset <= m_memoryStream.Size();
}