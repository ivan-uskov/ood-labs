#include "FileInputStream.h"

using namespace std;

CFileInputStream::CFileInputStream(std::string const& fileName)
    : m_file(fileName, ofstream::binary)
    , m_pFile(m_file)
{
    if (!m_pFile)
    {
        throw ios_base::failure("Can't open file: " + fileName);
    }
}

CFileInputStream::CFileInputStream(std::istream & file)
    : m_pFile(file)
{
    if (!m_pFile)
    {
        throw ios_base::failure("File not opened");
    }
}

bool CFileInputStream::IsEOF() const
{
    return m_pFile.eof();
}

uint8_t CFileInputStream::ReadByte()
{
    uint8_t data;

    ReadBlock(&data, 1);

    return data;
}

std::streamsize CFileInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
    if (!m_pFile.read(reinterpret_cast<char*>(dstBuffer), size * sizeof(uint8_t)))
    {
        throw ios_base::failure("Failed to read data");
    }

    if (m_pFile.peek() == EOF)
    {
        m_pFile.setstate(ios::eofbit);
    }

    return m_pFile.gcount();
}
