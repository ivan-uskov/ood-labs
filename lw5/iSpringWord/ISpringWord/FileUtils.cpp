#include "stdafx.h"
#include "FileUtils.h"
#include <boost/filesystem.hpp>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace boost::filesystem;

namespace FileUtils
{
    void CopyFile(const string & from, const string & to)
    {
        try
        {
            copy(from, to);
        }
        catch (const filesystem_error &)
        {
            throw runtime_error("Failed to make file copy");
        }
    }

    void CreateDirReqursively(const string & dirPath)
    {
        try
        {
            create_directories(path(dirPath));
        }
        catch (const filesystem_error &)
        {
            throw runtime_error("Failed to make file copy");
        }
    }

    bool Exists(string const& path)
    {
        return exists(path);
    }

    string GenerateUniqueFileName(const string & oldName)
    {
        auto extension = boost::filesystem::extension(oldName);
        auto timestamp = (system_clock::now()).time_since_epoch();
        return to_string(duration_cast<milliseconds>(timestamp).count()) + extension;
    }
}