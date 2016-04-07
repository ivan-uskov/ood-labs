#include "EncryptInputStreamDecorator.h"

using namespace std;

CEncryptInputStreamDecorator::CEncryptInputStreamDecorator(unique_ptr<IInputDataStream> && baseStream, unsigned seed)
    : CCryptInputStreamDecorator(move(baseStream), seed)
{}

uint8_t CEncryptInputStreamDecorator::CryptByte(uint8_t byte) const
{
    return m_replacementTable.replace(byte);
}