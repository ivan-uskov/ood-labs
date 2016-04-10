#include "stdafx.h"

#include "../streams/NumberReplacementTable.h"

using namespace std;

namespace
{
    auto GenerateTable()
    {
        return CNumberReplacementTable<uint8_t>(static_cast<unsigned>(rand()));
    }
}

BOOST_AUTO_TEST_SUITE(CheckUnsigned8BitConversions)

BOOST_AUTO_TEST_CASE(CheckConversionsClosed)
{
    auto table = GenerateTable();
    for (size_t num = std::numeric_limits<uint8_t>::min(); num <= std::numeric_limits<uint8_t>::max(); ++num)
    {
        BOOST_CHECK(num == table.unreplace(table.replace(static_cast<uint8_t>(num))));
    }
}

BOOST_AUTO_TEST_CASE(CheckConversionsNotEqual)
{
    auto table = GenerateTable();
    std::vector<uint8_t> bytes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto bytesCopy = bytes;
    std::transform(bytes.begin(), bytes.end(), bytes.begin(), [&table](auto & item) {
        return table.replace(item);
    });

    BOOST_CHECK(bytes != bytesCopy);
}

BOOST_AUTO_TEST_SUITE_END()