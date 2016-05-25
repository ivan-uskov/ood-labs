#include "stdafx.h"
#include "ImageDocumentItem.h"
#include "FileUtils.h"

using namespace std;

CImageDocumentItem::CImageDocumentItem(const string & path, size_t width, size_t height)
{
    m_image.Resize(width, height);
    auto imagePath = CopyToImagesDirectory(path);
    m_image = CImage(imagePath, width, height);
}

string CImageDocumentItem::GetDescription() const
{
    return "Image: " + to_string(m_image.GetWidth()) + " " + to_string(m_image.GetHeight()) + " " + m_image.GetPath();
}

void CImageDocumentItem::acceptExporter(IDocumentExportVisitor & visitor) const
{
    visitor.AddImage(m_image);
}

string CImageDocumentItem::CopyToImagesDirectory(const string & path) const
{
    if (!FileUtils::Exists(path))
    {
        throw invalid_argument("Image not exists");
    }

    auto copyPath = PrepareImageCopyPath(path);
    FileUtils::CopyFile(path, copyPath);

    return copyPath;
}

string CImageDocumentItem::PrepareImageCopyPath(const string & oldPath) const
{
    auto copyDir = "images";
    if (!FileUtils::Exists(copyDir))
    {
        FileUtils::CreateDirReqursively(copyDir);
    }

    return copyDir + string("/") + FileUtils::GenerateUniqueFileName(oldPath);
}
