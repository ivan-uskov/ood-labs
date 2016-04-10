#pragma once

#include "IInputDataStream.h"
#include <fstream>
#include <memory>

class CFileInputStream : public IInputDataStream
{
public:
    CFileInputStream(std::string const& fileName);
    CFileInputStream(std::istream & file);

    bool IsEOF()const override;
    uint8_t ReadByte() override;
    std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
    void UpdateEofBit();

    std::unique_ptr<std::istream> m_file;
};
