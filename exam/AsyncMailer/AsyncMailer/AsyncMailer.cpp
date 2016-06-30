#include "stdafx.h"
#include "Mail.h"
#include "MailSendCommand.h"
#include "MailQueue.h"
#include "MailQueueConsumer.h"

using namespace std;

unique_ptr<Mail> parseMail(string line)
{
    auto mail = make_unique<Mail>();
    istringstream strm(line);
    if (strm >> mail->recipient)
    {
        if (strm >> mail->message)
        {
            string otherWords;
            if (getline(strm, otherWords))
            {
                mail->message += otherWords;
            }
            return move(mail);
        }
    }

    return nullptr;
}

void runComsumer(shared_ptr<MailQueue> const& queue)
{
    (MailQueueConsumer(queue)).consume();
}

void readMails(shared_ptr<MailQueue> const& queue)
{
    bool success;
    do
    {
        string line;
        cout << "> ";
        success = bool(getline(cin, line));
        if (success)
        {
            auto mail = parseMail(line);
            if (mail)
            {
                auto mailCommand = make_unique<MailSendCommand>(move(mail));
                queue->addSendMailCommand(move(mailCommand));
                cout << "Mail added" << endl;
            }
            else
            {
                cout << "Unvalid mail format" << endl;
            }
        }
    } while (success);
}

int main()
{
    auto queue = make_shared<MailQueue>();
    auto fur = async(bind(runComsumer, queue));

    readMails(queue);
    queue->setNotAvailableForInsert();
    cout << "waiting for sends" << endl;

    fur.get();

    return 0;
}
