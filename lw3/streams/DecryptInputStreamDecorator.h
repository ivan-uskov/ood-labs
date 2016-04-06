#pragma once

#include "IInputDataStream.h"
#include "NumberReplacementTable.h"
#include <memory>

class CDecryptInputStreamDecorator : public IInputDataStream
{
public:
    CDecryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && baseStream, unsigned seed);

    bool IsEOF() const override;
    uint8_t ReadByte() override;
    std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
    std::unique_ptr<IInputDataStream> m_baseStream;
    CNumberReplacementTable<uint8_t> m_replacementTable;
};

