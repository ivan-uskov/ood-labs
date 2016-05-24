#include "stdafx.h"
#include "Menu.h"
#include "Document.h"
#include "TextUtils.h"

using namespace std;
using namespace std::placeholders;

namespace
{
    auto ReadInsertionPosition(istream & in)
    {
        boost::optional<size_t> position;
        string positionText;
        in >> positionText;

        if (positionText != "end")
        {
            position = size_t();
            if (!TextUtils::convertString(positionText, position.get()))
            {
                throw invalid_argument("Invalid position specified");
            }
        }

        return position;
    }

    size_t ReadNumber(istream & in, string const& errorMsg)
    {
        size_t number;

        if (!(in >> number))
        {
            throw invalid_argument(errorMsg);
        }

        return number;
    }

    auto ReadTextWithOutFirstSpaces(istream & in)
    {
        string head;
        string tail;

        if (in >> head)
        {
            getline(in, tail);
        }

        return head + tail;
    }

    void DoExceptionSafely(function<void()> && func)
    {
        try
        {
            func();
        }
        catch (exception const& e)
        {
            cout << e.what() << endl;
        }
    }

    class CEditor
    {
    public:
        CEditor()
            : m_document(make_unique<CDocument>())
        {
            m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
            m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
            AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
            AddMenuItem("insertParagraph", "Inserts paragraph. Args: <position|end> <text>", &CEditor::InsertParagraph);
            AddMenuItem("insertImage", "Inserts image. Args: <position|end> <width> <height> <path>", &CEditor::InsertImage);
            AddMenuItem("list", "Show document", &CEditor::List);
            AddMenuItem("undo", "Undo command", &CEditor::Undo);
            AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
        }

        void Start()
        {
            m_menu.Run();
        }

    private:
        typedef void (CEditor::*MenuHandler)(istream & in);

        void AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
        {
            m_menu.AddItem(shortcut, description, bind(handler, this, _1));
        }

        // TODO: скипнуть первый пробел элегантнее
        void SetTitle(istream & in)
        {
            auto title = ReadTextWithOutFirstSpaces(in);
            m_document->SetTitle(title);
        }

        void InsertParagraph(istream & in)
        {
            DoExceptionSafely([this, &in]() {
                auto position = ReadInsertionPosition(in);
                auto text = ReadTextWithOutFirstSpaces(in);
                m_document->InsertParagraph(text, position);
            });
        }

        void InsertImage(istream & in)
        {
            DoExceptionSafely([this, &in]() {
                auto position = ReadInsertionPosition(in);
                auto width = ReadNumber(in, "Invalid width specified");
                auto height = ReadNumber(in, "Invalid height specified");
                auto path = ReadTextWithOutFirstSpaces(in);
                m_document->InsertImage(path, width, height, position);
            });
        }

        void DeleteItem(istream & in)
        {
            DoExceptionSafely([this, &in]() {
                auto position = ReadInsertionPosition(in);
                if (position == boost::none)
                {
                    throw invalid_argument("Invalid position specified");
                }

                m_document->DeleteItem(*position);
            });
        }

        void List(istream &)
        {
            cout << "-------------" << endl;
            cout << "Title: " << m_document->GetTitle() << endl;

            for (size_t i = 0; i < m_document->GetItemsCount(); ++i)
            {
                cout << i << " " << m_document->GetItem(i).GetDescription() << endl;
            }
            cout << "-------------" << endl;
        }

        void Undo(istream &)
        {
            if (m_document->CanUndo())
            {
                m_document->Undo();
            }
            else
            {
                cout << "Can't undo" << endl;
            }
        }

        void Redo(istream &)
        {
            if (m_document->CanRedo())
            {
                m_document->Redo();
            }
            else
            {
                cout << "Can't redo" << endl;
            }
        }

        CMenu m_menu;
        unique_ptr<IDocument> m_document;
    };
}

int main()
{
    (CEditor()).Start();
    return 0;
}

