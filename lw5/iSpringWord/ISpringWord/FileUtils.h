#pragma once

namespace FileUtils
{
    void CopyFile(const std::string & from, const std::string & to);
    void CreateDirReqursively(const std::string & path);
    bool Exists(const std::string & path);
    std::string GenerateUniqueFileName(const std::string & oldName);
}