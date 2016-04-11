#include "stdafx.h"

//=================================================
#include <boost/test/included/unit_test.hpp>
//=================================================

using namespace std;

string GetFileContents(const string & fileName)
{
    ifstream file(fileName);
    return string((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
}