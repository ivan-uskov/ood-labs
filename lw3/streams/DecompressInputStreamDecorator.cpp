#include "DecompressInputStreamDecorator.h"

using namespace std;

CDecompressInputStreamDecorator::CDecompressInputStreamDecorator(unique_ptr<IInputDataStream> && baseStream)
    : m_baseStream(move(baseStream))
{}

bool CDecompressInputStreamDecorator::IsEOF() const
{
    return m_baseStream->IsEOF() && !m_buffer.size();
}

uint8_t CDecompressInputStreamDecorator::ReadByte()
{
    uint8_t data;

    ReadBlock(&data, 1);

    return data;
}

streamsize CDecompressInputStreamDecorator::ReadBlock(void * dstBuffer, streamsize size)
{
    UpdateBuffer(size);

    auto ptr = reinterpret_cast<uint8_t*>(dstBuffer);
    for (auto it = ptr; it < ptr + size; ++it)
    {
        *it = m_buffer.front();
        m_buffer.pop();
    };

    return size;
}

void CDecompressInputStreamDecorator::UpdateBuffer(std::streamsize size)
{
    while (m_buffer.size() < static_cast<size_t>(size))
    {
        Chunk chunk;
        m_baseStream->ReadBlock(reinterpret_cast<void*>(&chunk), 2);
        OpenChunk(chunk);
    }
}

void CDecompressInputStreamDecorator::OpenChunk(Chunk const& chunk)
{
    uint8_t countItems = chunk.count;
    while (countItems--)
    {
        m_buffer.push(chunk.val);
    }
}