#pragma once
#include <string>

class IImage
{
public:
    virtual std::string GetPath()const = 0;

    virtual size_t GetWidth()const = 0;
    virtual size_t GetHeight()const = 0;

    virtual void Resize(size_t width, size_t height) = 0;

    virtual ~IImage() = default;
};
