#pragma once

#include "IInputDataStream.h"
#include <memory>

class CEncryptInputStreamDecorator : public IInputDataStream
{
public:
    CEncryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && baseStream);

    bool IsEOF() const override;
    uint8_t ReadByte() override;
    std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
    std::unique_ptr<IInputDataStream> m_baseStream;
};

