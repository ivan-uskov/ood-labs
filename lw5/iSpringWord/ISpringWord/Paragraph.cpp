#include "stdafx.h"
#include "Paragraph.h"

CParagraph::CParagraph(const std::string & text)
    : m_value(text)
{}

std::string CParagraph::GetText()const
{
    return m_value;
}

void CParagraph::SetText(const std::string & text)
{
    m_value = text;
}