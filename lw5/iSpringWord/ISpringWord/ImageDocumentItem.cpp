#include "stdafx.h"
#include "ImageDocumentItem.h"
#include "FileUtils.h"

using namespace std;

CImageDocumentItem::CImageDocumentItem(const std::string & path, size_t width, size_t height)
{
    m_image.Resize(width, height);
    auto imagePath = CopyToImagesDirectory(path);
    m_image = CImage(imagePath, width, height);
}

std::string CImageDocumentItem::GetDescription() const
{
    return "Image: " + to_string(m_image.GetWidth()) + " " + to_string(m_image.GetHeight()) + " " + m_image.GetPath();
}

std::string CImageDocumentItem::CopyToImagesDirectory(const std::string & path) const
{
    if (!FileUtils::FileExists(path))
    {
        throw invalid_argument("Image not exists");
    }
    auto copyDir = "images";

    auto copyPath = copyDir + string("/") + FileUtils::GenerateUniqueFileName(path);

    if (!FileUtils::CopyFile(path, copyPath))
    {
        throw runtime_error("Failed to make file copy");
    }

    return copyPath;
}
