#include "stdafx.h"
#include "ParagraphDocumentItem.h"


CParagraphDocumentItem::CParagraphDocumentItem(std::string text)
    : m_paragraph(text)
{
}

std::string CParagraphDocumentItem::GetDescription() const
{
    return "Paragraph: " + m_paragraph.GetText();
}