#pragma once
#include "IMailSendCommand.h"

class MailQueue
{
public:
    void addSendMailCommand(MailSendCommandPtr && mail);
    MailSendCommandPtr getSendMailCommand();

    bool isEmpty() const;
    bool isAvailableForInsert() const;
    void setNotAvailableForInsert();

private:
    std::queue<MailSendCommandPtr> m_queue;
    std::mutex m_queueMutex;
    std::atomic_bool m_isAvailableForInsert = true;
};

