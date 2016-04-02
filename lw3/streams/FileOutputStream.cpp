#include "FileOutputStream.h"

using namespace std;

CFileOutputStream::CFileOutputStream(string const& fileName)
    : m_file(fileName, fstream::out | fstream::binary)
{
    if (!m_file)
    {
        throw ios_base::failure("Can't create file: " + fileName);
    }
}

void CFileOutputStream::WriteByte(uint8_t data)
{
    WriteBlock(&data, sizeof(uint8_t));
}

void CFileOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
    if (!m_file.write(reinterpret_cast<const char*>(srcData), size))
    {
        throw ios_base::failure("Failed to write data");
    }
}