#include "MemoryOutputStream.h"

using namespace std;

CMemoryOutputStream::CMemoryOutputStream(IMemoryStream<uint8_t> & memoryStream)
    : m_memoryStream(memoryStream)
{}

void CMemoryOutputStream::WriteByte(uint8_t data)
{
    WriteBlock(&data, 1);
}

void CMemoryOutputStream::WriteBlock(const void * srcData, streamsize size)
{
    auto bufferPtr = reinterpret_cast<const uint8_t*>(srcData);
    for (streamsize i = 0; i < size; ++i)
    {
        m_memoryStream.Add(*(bufferPtr++));
    }
}