#pragma once

#include "IOutputDataStream.h"
#include <fstream>

class CFileOutputStream : IOutputDataStream
{
public:
    CFileOutputStream(std::string const& fileName);

    void WriteByte(uint8_t data) override;
    void WriteBlock(const void * srcData, std::streamsize size) override;

private:
    std::fstream m_file;
};

