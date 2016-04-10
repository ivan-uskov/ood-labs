#pragma once

#include "CryptInputStreamDecorator.h"

class CEncryptInputStreamDecorator : public CCryptInputStreamDecorator
{
public:
    CEncryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && baseStream, unsigned seed);
protected:
    uint8_t CryptByte(uint8_t) const override;
};

