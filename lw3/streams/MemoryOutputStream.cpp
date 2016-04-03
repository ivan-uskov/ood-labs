#include "MemoryOutputStream.h"

CMemoryOutputStream::CMemoryOutputStream(IMemoryStream<uint8_t> & memoryStream)
    : m_memoryStream(memoryStream)
{}

void CMemoryOutputStream::WriteByte(uint8_t data)
{
    WriteBlock(&data, 1);
}

void CMemoryOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
    auto bufferPtr = reinterpret_cast<const uint8_t*>(srcData);
    for (size_t i = 0; i < size; ++i)
    {
        m_memoryStream.Add(*(bufferPtr++));
    }
}