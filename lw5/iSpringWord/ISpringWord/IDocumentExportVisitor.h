#pragma once

#include "IImage.h"
#include "IParagraph.h"

class IDocumentExportVisitor
{
public:
    virtual void AddImage(const IImage & image) = 0;
    virtual void AddParagraph(const IParagraph & paragraph) = 0;

    virtual ~IDocumentExportVisitor() = default;
};