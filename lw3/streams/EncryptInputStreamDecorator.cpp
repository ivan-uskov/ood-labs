#include "EncryptInputStreamDecorator.h"

using namespace std;

CEncryptInputStreamDecorator::CEncryptInputStreamDecorator(unique_ptr<IInputDataStream> && baseStream)
    : m_baseStream(move(baseStream))
{}

bool CEncryptInputStreamDecorator::IsEOF() const
{
    return m_baseStream->IsEOF();
}

uint8_t CEncryptInputStreamDecorator::ReadByte()
{
    return 1;
}

streamsize CEncryptInputStreamDecorator::ReadBlock(void * dstBuffer, streamsize size)
{
    return 1;
}
