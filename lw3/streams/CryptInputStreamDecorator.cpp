#include "CryptInputStreamDecorator.h"

using namespace std;

CCryptInputStreamDecorator::CCryptInputStreamDecorator(unique_ptr<IInputDataStream> && baseStream, unsigned seed)
    : m_baseStream(move(baseStream))
    , m_replacementTable(seed)
{}

bool CCryptInputStreamDecorator::IsEOF() const
{
    return m_baseStream->IsEOF();
}

uint8_t CCryptInputStreamDecorator::ReadByte()
{
    return CryptByte(m_baseStream->ReadByte());
}

streamsize CCryptInputStreamDecorator::ReadBlock(void * dstBuffer, streamsize size)
{
    auto bytesReaded = m_baseStream->ReadBlock(dstBuffer, size);

    auto ptr = reinterpret_cast<uint8_t*>(dstBuffer);
    for (auto it = ptr; it < ptr + bytesReaded; ++it)
    {
        *it = CryptByte(*it);
    };

    return bytesReaded;
}