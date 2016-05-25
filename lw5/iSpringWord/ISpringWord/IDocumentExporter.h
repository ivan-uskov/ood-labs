#pragma once

#include "IDocumentExportVisitor.h"

class IDocumentExporter : public IDocumentExportVisitor
{
public:
    virtual void Generate() = 0;
};