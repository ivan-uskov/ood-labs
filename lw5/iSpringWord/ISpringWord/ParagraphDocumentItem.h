#pragma once
#include "DocumentItem.h"
#include "Paragraph.h"

class CParagraphDocumentItem : public CDocumentItem
{
public:
    CParagraphDocumentItem(std::string text);

    std::string GetDescription() const override;

private:
    CParagraph m_paragraph;
};

