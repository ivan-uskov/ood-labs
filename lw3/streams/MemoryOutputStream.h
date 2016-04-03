#pragma once

#include "IOutputDataStream.h"
#include "IMemoryStream.h"

class CMemoryOutputStream : public IOutputDataStream
{
public:
    CMemoryOutputStream(IMemoryStream<uint8_t> & memoryStream);

    void WriteByte(uint8_t data) override;
    void WriteBlock(const void * srcData, std::streamsize size) override;

private:
    IMemoryStream<uint8_t> & m_memoryStream;
};

