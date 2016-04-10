#pragma once

#include "IInputDataStream.h"
#include <fstream>

class CFileInputStream : public IInputDataStream
{
public:
    CFileInputStream(std::string const& fileName);
    CFileInputStream(std::istream & file);

    bool IsEOF()const override;
    uint8_t ReadByte() override;
    std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
    std::istream & m_pFile;
    std::ifstream m_file;
};
