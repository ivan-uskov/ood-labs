#pragma once

#include "IOutputDataStream.h"
#include <memory>

class CCompressOutputStreamDecorator : public IOutputDataStream
{
public:
    CCompressOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && baseStream);
    ~CCompressOutputStreamDecorator();

    void WriteByte(uint8_t data) override;
    void WriteBlock(const void * srcData, std::streamsize size) override;

private:
    struct Chunk
    {
        uint8_t val, count;
    };

    void CreateChunk(uint8_t val);
    void FlushChunk();

    std::unique_ptr<Chunk> m_chunk;
    std::unique_ptr<IOutputDataStream> m_baseStream;
};

