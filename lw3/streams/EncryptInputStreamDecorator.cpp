#include "EncryptInputStreamDecorator.h"

using namespace std;

CEncryptInputStreamDecorator::CEncryptInputStreamDecorator(unique_ptr<IInputDataStream> && baseStream, unsigned seed)
    : m_baseStream(move(baseStream))
    , m_replacementTable(seed)
{}

bool CEncryptInputStreamDecorator::IsEOF() const
{
    return m_baseStream->IsEOF();
}

uint8_t CEncryptInputStreamDecorator::ReadByte()
{
    return m_replacementTable.replace(m_baseStream->ReadByte());
}

streamsize CEncryptInputStreamDecorator::ReadBlock(void * dstBuffer, streamsize size)
{
    auto bytesReaded = m_baseStream->ReadBlock(dstBuffer, size);

    auto ptr = reinterpret_cast<uint8_t*>(dstBuffer);
    for (auto it = ptr; it < ptr + bytesReaded; ++it)
    {
        *it = m_replacementTable.replace(*it);
    };

    return bytesReaded;
}
