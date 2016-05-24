#pragma once

#include "IImage.h"

class CImage : public IImage
{
public:
    CImage() = default;
    CImage(const std::string & path, size_t width, size_t height);

    std::string GetPath()const override;
    size_t GetWidth()const override;
    size_t GetHeight()const override;
    void Resize(size_t width, size_t height) override;

private:
    std::string m_path;
    size_t m_width = 0;
    size_t m_height = 0;
};