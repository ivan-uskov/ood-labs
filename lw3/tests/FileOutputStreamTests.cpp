#include "stdafx.h"

#include "../streams/FileOutputStream.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FileOutputStreamTests)

BOOST_AUTO_TEST_CASE(CheckWriteBite)
{
    {
        CFileOutputStream out("not_existing_file");
        out.WriteByte('4');
    }

    BOOST_CHECK_EQUAL(GetFileContents("not_existing_file"), to_string(4));

    remove("not_existing_file");
}

BOOST_AUTO_TEST_CASE(CheckWriteBlock)
{
    {
        CFileOutputStream out("not_existing_file");
        out.WriteBlock("1234", 4);
    }

    BOOST_CHECK_EQUAL(GetFileContents("not_existing_file"), string("1234"));

    remove("not_existing_file");
}

BOOST_AUTO_TEST_SUITE_END()