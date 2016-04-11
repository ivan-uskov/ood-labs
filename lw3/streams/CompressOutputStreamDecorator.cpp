#include "CompressOutputStreamDecorator.h"

using namespace std;

CCompressOutputStreamDecorator::CCompressOutputStreamDecorator(unique_ptr<IOutputDataStream> && baseStream)
    : m_baseStream(move(baseStream))
{
}

void CCompressOutputStreamDecorator::WriteByte(uint8_t data)
{

}

void CCompressOutputStreamDecorator::WriteBlock(const void * srcData, streamsize size)
{

}