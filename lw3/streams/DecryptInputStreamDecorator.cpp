#include "DecryptInputStreamDecorator.h"

using namespace std;


CDecryptInputStreamDecorator::CDecryptInputStreamDecorator(unique_ptr<IInputDataStream> && baseStream, unsigned seed)
    : m_baseStream(move(baseStream))
    , m_replacementTable(seed)
{}

bool CDecryptInputStreamDecorator::IsEOF() const
{
    return m_baseStream->IsEOF();
}

uint8_t CDecryptInputStreamDecorator::ReadByte()
{
    return m_replacementTable.unreplace(m_baseStream->ReadByte());
}

streamsize CDecryptInputStreamDecorator::ReadBlock(void * dstBuffer, streamsize size)
{
    auto bytesReaded = m_baseStream->ReadBlock(dstBuffer, size);

    auto ptr = reinterpret_cast<uint8_t*>(dstBuffer);
    for (auto it = ptr; it < ptr + bytesReaded; ++it)
    {
        *it = m_replacementTable.unreplace(*it);
    };

    return bytesReaded;
}
