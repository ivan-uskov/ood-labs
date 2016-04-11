#include "CompressOutputStreamDecorator.h"

using namespace std;

CCompressOutputStreamDecorator::CCompressOutputStreamDecorator(unique_ptr<IOutputDataStream> && baseStream)
    : m_baseStream(move(baseStream))
{
}

CCompressOutputStreamDecorator::~CCompressOutputStreamDecorator()
{
    FlushChunk();
}

void CCompressOutputStreamDecorator::WriteByte(uint8_t data)
{
    if (!m_chunk)
    {
        CreateChunk(data);
    }
    else if (m_chunk->val == data && m_chunk->count < std::numeric_limits<uint8_t>::max())
    {
        ++m_chunk->count;
    }
    else
    {
        FlushChunk();
        CreateChunk(data);
    }
}

void CCompressOutputStreamDecorator::WriteBlock(const void * srcData, streamsize size)
{
    auto bufferPtr = reinterpret_cast<const uint8_t*>(srcData);
    for (streamsize i = 0; i < size; ++i)
    {
        WriteByte(*(bufferPtr++));
    }
}

void CCompressOutputStreamDecorator::CreateChunk(uint8_t val)
{
    m_chunk = make_unique<Chunk>();
    m_chunk->val = val;
    m_chunk->count = 1;
}

void CCompressOutputStreamDecorator::FlushChunk()
{
    m_baseStream->WriteBlock(m_chunk.get(), 2);
    m_chunk.reset();
}