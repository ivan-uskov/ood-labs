#pragma once

#include "IDocumentItem.h"
#include "Image.h"

class CImageDocumentItem : public IDocumentItem
{
public:
    CImageDocumentItem(const std::string & path, size_t width, size_t height);

    std::string GetDescription() const override;
    void acceptExporter(IDocumentExportVisitor & visitor) const override;

private:
    std::string CopyToImagesDirectory(const std::string & path) const;
    std::string PrepareImageCopyPath(const std::string & oldPath) const;

    CImage m_image;
};

