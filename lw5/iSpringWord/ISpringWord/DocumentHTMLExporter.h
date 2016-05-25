#pragma once

#include "IDocument.h"
#include "IDocumentExporter.h"

class CDocumentHTMLExporter : public IDocumentExporter
{
public:
    CDocumentHTMLExporter(const IDocument & document, std::ostream & out);

    void AddImage(const IImage & image) override;
    void AddParagraph(const IParagraph & paragraph) override;

    void Generate() override;

private:
    void WriteTopPart();
    void WriteBottomPart();
    void WriteDocumentItems();
    void AddBodyItem(const std::string & item);

    const IDocument & m_document;
    std::ostream & m_out;
};