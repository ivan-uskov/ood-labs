#include "stdafx.h"
#include "FileUtils.h"
#include <boost/filesystem.hpp>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace boost::filesystem;

namespace FileUtils
{
    bool CopyFile(std::string const& from, std::string const& to)
    {
        try
        {
            copy(from, to);
            return true;
        }
        catch (filesystem_error const&)
        {
            return false;
        }
    }

    bool FileExists(std::string const& path)
    {
        return exists(path);
    }

    std::string GenerateUniqueFileName(std::string const& oldName)
    {
        auto extension = boost::filesystem::extension(oldName);
        auto timestamp = (system_clock::now()).time_since_epoch();
        return to_string(duration_cast<milliseconds>(timestamp).count()) + "." + extension;
    }
}