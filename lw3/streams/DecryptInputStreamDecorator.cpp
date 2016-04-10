#include "DecryptInputStreamDecorator.h"

using namespace std;

CDecryptInputStreamDecorator::CDecryptInputStreamDecorator(unique_ptr<IInputDataStream> && baseStream, unsigned seed)
    : CCryptInputStreamDecorator(move(baseStream), seed)
{}

uint8_t CDecryptInputStreamDecorator::CryptByte(uint8_t byte) const
{
    return m_replacementTable.unreplace(byte);
}
