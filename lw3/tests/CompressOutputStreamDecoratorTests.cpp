#include "stdafx.h"

#include "../streams/FileOutputStream.h"
#include "../streams/CompressOutputStreamDecorator.h"

using namespace std;

namespace
{
    auto CreateCompressOutputStream(const string & fileName)
    {
        return make_unique<CCompressOutputStreamDecorator>(make_unique<CFileOutputStream>(fileName));
    }

    auto GetCompressedBytesString(size_t bytesCount)
    {
        return to_string(4) + static_cast<char>(bytesCount) + to_string(5) + static_cast<char>(bytesCount);
    }
}

BOOST_AUTO_TEST_CASE(CheckCompressByte)
{
    size_t bytesCount = 20;
    {
        auto out = CreateCompressOutputStream("not_existing_file1");
        for (size_t i = 0; i < bytesCount; ++i)
        {
            out->WriteByte('4');
        }

        for (size_t i = 0; i < bytesCount; ++i)
        {
            out->WriteByte('5');
        }
    }

    BOOST_CHECK_EQUAL(GetFileContents("not_existing_file1"), GetCompressedBytesString(bytesCount));

    remove("not_existing_file");
}

BOOST_AUTO_TEST_CASE(CheckCompressBlock)
{
    size_t bytesCount = 20;
    {
        auto out = CreateCompressOutputStream("not_existing_file");
        string block;
        for (size_t i = 0; i < bytesCount; ++i)
        {
            block += '4';
        }
        out->WriteBlock(block.data(), bytesCount);

        block.clear();
        for (size_t i = 0; i < bytesCount; ++i)
        {
            block += '5';
        }
        out->WriteBlock(block.data(), bytesCount);
    }

    BOOST_CHECK_EQUAL(GetFileContents("not_existing_file"), GetCompressedBytesString(bytesCount));

    remove("not_existing_file");
}