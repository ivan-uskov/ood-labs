#include "stdafx.h"

#include "../streams/FileInputStream.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FileInputStreamTests)

BOOST_AUTO_TEST_CASE(CheckOpenEmptyFile)
{
    BOOST_CHECK_THROW(CFileInputStream("not_existing_file"), ios::failure);
}

BOOST_AUTO_TEST_SUITE_END()