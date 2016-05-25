#include "stdafx.h"
#include "DocumentHTMLExporter.h"
#include <boost/format.hpp>

using namespace std;

CDocumentHTMLExporter::CDocumentHTMLExporter(const IDocument & document, ostream & out)
    : m_document(document)
    , m_out(out)
{}

void CDocumentHTMLExporter::AddImage(const IImage & image)
{
    AddBodyItem((
        boost::format(R"(<img src="%1%" width="%2%" height="%3%" />)")
        % image.GetPath()
        % image.GetWidth()
        % image.GetHeight()
    ).str());
}

void CDocumentHTMLExporter::AddParagraph(const IParagraph & paragraph)
{
    AddBodyItem("<p>" + paragraph.GetText() + "</p>");
}

void CDocumentHTMLExporter::Generate()
{
    WriteTopPart();
    WriteDocumentItems();
    WriteBottomPart();
}

void CDocumentHTMLExporter::WriteTopPart()
{
    m_out << R"(<!DOCTYPE html>
<html>
    <head>
        <title>)" << m_document.GetTitle() << R"(</title>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    </head>
    <body>
)";
}

void CDocumentHTMLExporter::WriteBottomPart()
{
    m_out << R"(</body>
</html>
)";
}

void CDocumentHTMLExporter::WriteDocumentItems()
{
    for (size_t i = 0; i < m_document.GetItemsCount(); ++i)
    {
        m_document.GetItem(i).acceptExporter(*this);
    }
}

void CDocumentHTMLExporter::AddBodyItem(const string & item)
{
    m_out << "        " << item << endl;
}