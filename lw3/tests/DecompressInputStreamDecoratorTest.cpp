#include "stdafx.h"

#include "../streams/FileInputStream.h"
#include "../streams/DecompressInputStreamDecorator.h"

using namespace std;

namespace
{
    auto CreateDecompressInputStream(string const& fileName)
    {
        return make_unique<CDecompressInputStreamDecorator>(make_unique<CFileInputStream>(fileName));
    }
}

BOOST_AUTO_TEST_SUITE(DecompressOutputStreamTests)

BOOST_AUTO_TEST_CASE(CheckDecompressByte)
{
    BOOST_CHECK_THROW(CFileInputStream("not_existing_file"), ios::failure);

    {
        ofstream("not_existing_file") << 'A' << uint8_t(5);
        BOOST_CHECK_NO_THROW(CFileInputStream("not_existing_file"));
    }

    {
        string buffer;
        auto stream = CreateDecompressInputStream("not_existing_file");
        while (!stream->IsEOF())
        {
            uint8_t byte;
            BOOST_CHECK_NO_THROW(byte = stream->ReadByte());
            buffer += static_cast<char>(byte);
        }

        BOOST_CHECK_EQUAL(buffer, string("AAAAA"));
    }

    remove("not_existing_file");
}

BOOST_AUTO_TEST_SUITE_END()