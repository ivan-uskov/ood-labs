#pragma once

#include "IOutputDataStream.h"
#include <memory>

class CCompressOutputStreamDecorator : public IOutputDataStream
{
public:
    CCompressOutputStreamDecorator(std::unique_ptr<IOutputDataStream> && baseStream);

private:
    std::unique_ptr<IOutputDataStream> m_baseStream;
};

