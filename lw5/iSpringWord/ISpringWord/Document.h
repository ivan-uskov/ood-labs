#pragma once
#include "IDocument.h"
#include "History.h"
#include "DocumentItem.h"

class CDocument : public IDocument
{
public:

    void SetTitle(const std::string & title) override;
    std::string GetTitle() const override;

    std::shared_ptr<IParagraph> InsertParagraph(const std::string & text, boost::optional<size_t> position = boost::none) override;

    size_t GetItemsCount()const override;
    void DeleteItem(size_t index) override;

    CConstDocumentItem const& GetItem(size_t index)const override;
    CDocumentItem & GetItem(size_t index) override;

    bool CanUndo() const override;
    void Undo() override;
    bool CanRedo() const override;
    void Redo() override;

private:
    std::deque<std::shared_ptr<CDocumentItem>> m_items;
    std::string m_title;
    CHistory m_history;
};