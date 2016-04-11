#include "stdafx.h"

#include "../streams/FileInputStream.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FileInputStreamTests)

BOOST_AUTO_TEST_CASE(CheckOpenEmptyFile)
{
    BOOST_CHECK_THROW(CFileInputStream("not_existing_file"), ios::failure);

    {
        ofstream("not_existing_file");
        BOOST_CHECK_NO_THROW(CFileInputStream("not_existing_file"));
    }

    {
        CFileInputStream in("not_existing_file");
        BOOST_CHECK_EQUAL(in.IsEOF(), true);
    }

    remove("not_existing_file");
}

BOOST_AUTO_TEST_CASE(CheckReadByte)
{
    string bytes("0123456789");
    {
        ofstream("not_existing_file") << bytes;
    }

    CFileInputStream in("not_existing_file");
    BOOST_CHECK_EQUAL(in.IsEOF(), false);

    std::for_each(bytes.begin(), bytes.end(), [&](auto & currChar) {
        uint8_t byte = in.ReadByte();
        BOOST_CHECK_EQUAL(byte, currChar);
    });

    BOOST_CHECK_EQUAL(in.IsEOF(), true);

    remove("not_existing_file");
}

BOOST_AUTO_TEST_CASE(CheckReadBlock)
{
    string bytes("0123456789");
    {
        ofstream("not_existing_file") << bytes;
    }

    std::array<uint8_t, 10> myBlock;

    {
        CFileInputStream in("not_existing_file");
        BOOST_CHECK_EQUAL(in.IsEOF(), false);

        streamsize redCount;
        BOOST_CHECK_NO_THROW(redCount = in.ReadBlock(myBlock.data(), 5));
        BOOST_CHECK_EQUAL(redCount, 5);
        BOOST_CHECK_EQUAL(in.IsEOF(), false);

        BOOST_CHECK_NO_THROW(redCount = in.ReadBlock(myBlock.data() + 5, 5));
        BOOST_CHECK_EQUAL(redCount, 5);
        BOOST_CHECK_EQUAL(in.IsEOF(), true);
    }

    remove("not_existing_file");

    for (size_t i = 0; i < myBlock.size(); ++i)
    {
        BOOST_CHECK_EQUAL(myBlock[i], bytes[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()