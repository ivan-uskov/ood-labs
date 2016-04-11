#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <array>
#include <iostream>
#include <fstream>


///=======================================
#define BOOST_TEST_MODULE DecoratorProjectsTest
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702)
#include <boost/test/unit_test.hpp>
///=======================================

std::string GetFileContents(const std::string & fileName);