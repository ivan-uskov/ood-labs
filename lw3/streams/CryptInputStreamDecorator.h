#pragma once

#include "NumberReplacementTable.h"
#include "IInputDataStream.h"
#include <memory>

class CCryptInputStreamDecorator : public IInputDataStream
{
public:
    CCryptInputStreamDecorator(std::unique_ptr<IInputDataStream> && baseStream, unsigned seed);

    bool IsEOF() const override;
    uint8_t ReadByte() override;
    std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

protected:
    virtual uint8_t CryptByte(uint8_t) const = 0;

    CNumberReplacementTable<uint8_t> m_replacementTable;

private:
    std::unique_ptr<IInputDataStream> m_baseStream;
};

