#pragma once
#include "IDocumentItem.h"
#include "Paragraph.h"

class CParagraphDocumentItem : public IDocumentItem
{
public:
    CParagraphDocumentItem(std::string text);

    std::string GetDescription() const override;
    void acceptExporter(IDocumentExportVisitor & visitor) const override;

private:
    CParagraph m_paragraph;
};

