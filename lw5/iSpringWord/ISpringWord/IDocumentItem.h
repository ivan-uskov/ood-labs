#pragma once

#include "IDocumentExportVisitor.h"

class IDocumentItem
{
public:
    virtual std::string GetDescription() const = 0;
    virtual void acceptExporter(IDocumentExportVisitor & visitor) const = 0;

    virtual ~IDocumentItem() = default;
};
