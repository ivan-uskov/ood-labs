#pragma once

namespace FileUtils
{
    bool CopyFile(std::string const& from, std::string const& to);
    bool FileExists(std::string const& path);
    std::string GenerateUniqueFileName(std::string const& oldName);
}