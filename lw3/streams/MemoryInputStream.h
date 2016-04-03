#pragma once

#include "IInputDataStream.h"
#include "IMemoryStream.h"

class CMemoryInputStream : public IInputDataStream
{
public:
    CMemoryInputStream(IMemoryStream<uint8_t> & memoryStream);

    bool IsEOF() const override;
    uint8_t ReadByte() override;
    std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
    bool HasUnreadData(size_t size) const;

    IMemoryStream<uint8_t> & m_memoryStream;
    size_t m_offset = 0;
};
