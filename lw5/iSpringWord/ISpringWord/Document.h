#pragma once
#include "IDocument.h"
#include "History.h"
#include "IDocumentItem.h"

class CDocument : public IDocument
{
public:

    void SetTitle(const std::string & title) override;
    std::string GetTitle() const override;

    void InsertParagraph(const std::string & text, boost::optional<size_t> position = boost::none) override;
    void InsertImage(const std::string & path, size_t width, size_t height, boost::optional<size_t> position = boost::none) override;

    size_t GetItemsCount()const override;
    void DeleteItem(size_t index) override;

    IDocumentItem const& GetItem(size_t index)const override;
    IDocumentItem & GetItem(size_t index) override;

    bool CanUndo() const override;
    void Undo() override;
    bool CanRedo() const override;
    void Redo() override;

private:
    void verifyInsertionPosition(boost::optional<size_t> const& position) const;

    std::deque<std::shared_ptr<IDocumentItem>> m_items;
    std::string m_title;
    CHistory m_history;
};