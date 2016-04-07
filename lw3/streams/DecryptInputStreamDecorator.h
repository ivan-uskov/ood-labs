#pragma once

#include "CryptInputStreamDecorator.h"

class CDecryptInputStreamDecorator : public CCryptInputStreamDecorator
{
public:
    CDecryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && baseStream, unsigned seed);

protected:
    uint8_t CryptByte(uint8_t) const override;
};

