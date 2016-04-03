#pragma once

template <typename T>
class IMemoryStream
{
public:
    virtual size_t Size() const = 0;
    virtual T & operator [] (size_t idx) = 0;
    virtual T const& operator [] (size_t idx) const = 0;

    virtual void Add(T const& value) = 0;
    virtual void Remove(size_t idx) = 0;

    virtual ~IMemoryStream() = default;
};
