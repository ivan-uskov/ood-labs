#include "FileInputStream.h"

using namespace std;

CFileInputStream::CFileInputStream(std::string const& fileName)
    : m_file(make_unique<ifstream>(fileName, ofstream::binary))
{
    if (!m_file || !(*m_file))
    {
        throw ios_base::failure("Can't open file: " + fileName);
    }

    UpdateEofBit();
}

CFileInputStream::CFileInputStream(std::istream & file)
    : m_file(addressof(file))
{
    if (!m_file || !(*m_file))
    {
        throw ios_base::failure("File not opened");
    }

    UpdateEofBit();
}

bool CFileInputStream::IsEOF() const
{
    return m_file && m_file->eof();
}

uint8_t CFileInputStream::ReadByte()
{
    uint8_t data;

    ReadBlock(&data, 1);

    return data;
}

std::streamsize CFileInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
    if (!m_file->read(reinterpret_cast<char*>(dstBuffer), size * sizeof(uint8_t)))
    {
        throw ios_base::failure("Failed to read data");
    }

    auto bytesRed = m_file->gcount();

    UpdateEofBit();

    return bytesRed;
}

void CFileInputStream::UpdateEofBit()
{
    if (m_file->peek() == EOF)
    {
        m_file->setstate(ios::eofbit);
    }
}

