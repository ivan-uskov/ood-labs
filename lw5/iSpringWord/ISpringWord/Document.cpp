#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "ParagraphDocumentItem.h"
#include "ImageDocumentItem.h"

using namespace std;

shared_ptr<IImage> CDocument::InsertImage(const string & path, size_t width, size_t height, boost::optional<size_t> position)
{
    verifyInsertionPosition(position);

    m_history.AddAndExecuteCommand(
        make_unique<CInsertItemCommand<decltype(m_items)>>(
            m_items,
            make_shared<CImageDocumentItem>(path, width, height),
            position
        )
    );

    return m_items[position ? *position : m_items.size() - 1]->GetImage();
}

shared_ptr<IParagraph> CDocument::InsertParagraph(const string & text, boost::optional<size_t> position)
{
    verifyInsertionPosition(position);

    m_history.AddAndExecuteCommand(
        make_unique<CInsertItemCommand<decltype(m_items)>>(
            m_items,
            make_shared<CParagraphDocumentItem>(text), 
            position
        )
    );

    return m_items[position ? *position : m_items.size() - 1]->GetParagraph();
}

void CDocument::DeleteItem(size_t index)
{
    if (index >= GetItemsCount())
    {
        throw invalid_argument("Invalid position specified");
    }

    m_history.AddAndExecuteCommand(
        make_unique<CDeleteItemCommand<decltype(m_items)>>(m_items, index)
    );
}

size_t CDocument::GetItemsCount() const
{
    return m_items.size();
}

CConstDocumentItem const& CDocument::GetItem(size_t index) const
{
    if (index >= m_items.size())
    {
        throw invalid_argument("Invalid item index");
    }

    return *m_items[index];
}

CDocumentItem & CDocument::GetItem(size_t index)
{
    if (index >= m_items.size())
    {
        throw invalid_argument("Invalid item index");
    }

    return *m_items[index];
}

void CDocument::SetTitle(const std::string & title)
{
    m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
    return m_title;
}

bool CDocument::CanUndo() const
{
    return m_history.CanUndo();
}

void CDocument::Undo()
{
    m_history.Undo();
}

bool CDocument::CanRedo() const
{
    return m_history.CanRedo();
}

void CDocument::Redo()
{
    m_history.Redo();
}

void CDocument::verifyInsertionPosition(boost::optional<size_t> const& position) const
{
    if (position != boost::none && *position >= GetItemsCount())
    {
        throw invalid_argument("Invalid position specified");
    }
}