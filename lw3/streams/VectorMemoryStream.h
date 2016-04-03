#pragma once

#include "IMemoryStream.h"
#include <stdint.h>
#include <vector>

class CVectorMemoryStream : public IMemoryStream<uint8_t>
{
public:
    size_t Size() const override;
    uint8_t & operator [] (size_t idx) override;
    uint8_t const& operator [] (size_t idx) const override;

    void Add(uint8_t const& value) override;
    void Remove(size_t idx) override;

private:
    std::vector<uint8_t> m_memory;
};

