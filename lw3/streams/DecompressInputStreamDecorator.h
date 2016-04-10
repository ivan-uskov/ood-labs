#pragma once
#include "IInputDataStream.h"
#include <memory>
#include <queue>

class CDecompressInputStreamDecorator : public IInputDataStream
{
public:
    CDecompressInputStreamDecorator(std::unique_ptr<IInputDataStream> && baseStream);

    bool IsEOF() const override;
    uint8_t ReadByte() override;
    std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
    struct Chunk
    {
        uint8_t val, count;
    };

    void UpdateBuffer(std::streamsize size);
    void OpenChunk(Chunk const& chunk);

    std::queue<uint8_t> m_buffer;
    std::unique_ptr<IInputDataStream> m_baseStream;
};

