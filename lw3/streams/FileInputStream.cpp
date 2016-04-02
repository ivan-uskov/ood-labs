#include "FileInputStream.h"

using namespace std;

CFileInputStream::CFileInputStream(std::string const& fileName)
    : m_file(fileName, std::fstream::in | std::fstream::binary)
{
    if (!m_file)
    {
        throw ios_base::failure("Can't open file: " + fileName);
    }
}

bool CFileInputStream::IsEOF() const
{
    return m_file.eof();
}

uint8_t CFileInputStream::ReadByte()
{
    uint8_t data;

    ReadBlock(&data, sizeof(uint8_t));

    return data;
}

std::streamsize CFileInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
    if (!m_file.read(reinterpret_cast<char*>(dstBuffer), size))
    {
        throw ios_base::failure("Failed to read data");
    }

    return m_file.gcount();
}
