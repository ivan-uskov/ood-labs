#pragma once

#include "DocumentItem.h"
#include "Image.h"

class CImageDocumentItem : public CDocumentItem
{
public:
    CImageDocumentItem(const std::string & path, size_t width, size_t height);

    std::string GetDescription() const override;

private:
    std::string CopyToImagesDirectory(const std::string & path) const;

    CImage m_image;
};

