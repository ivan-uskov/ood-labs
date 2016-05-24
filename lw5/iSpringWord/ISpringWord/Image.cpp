#include "stdafx.h"
#include "Image.h"

using namespace std;

CImage::CImage(const std::string & path, size_t width, size_t height)
    : m_path(path)
{
    Resize(width, height);
}

std::string CImage::GetPath()const
{
    return m_path;
}

size_t CImage::GetWidth()const
{
    return m_width;
}

size_t CImage::GetHeight()const
{
    return m_height;
}

void CImage::Resize(size_t width, size_t height)
{
    static const size_t MAX_DIMENSION_SIZE = 10000;

    if (width > MAX_DIMENSION_SIZE)
    {
        throw invalid_argument("Invalid width specified");
    }

    if (height > MAX_DIMENSION_SIZE)
    {
        throw invalid_argument("Invalid height specified");
    }

    m_width = width;
    m_height = height;
}