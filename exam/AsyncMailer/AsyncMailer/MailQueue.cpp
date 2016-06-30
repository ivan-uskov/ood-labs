#include "stdafx.h"
#include "MailQueue.h"

using namespace std;

void MailQueue::addSendMailCommand(MailSendCommandPtr && mail)
{
    m_queueMutex.lock();
    m_queue.push(move(mail));
    m_queueMutex.unlock();
}

MailSendCommandPtr MailQueue::getSendMailCommand()
{
    MailSendCommandPtr ptr;

    m_queueMutex.lock();
    if (!m_queue.empty())
    {
        ptr = move(m_queue.front());
        m_queue.pop();
    }
    m_queueMutex.unlock();

    return move(ptr);
}

bool MailQueue::isEmpty() const
{
    return m_queue.empty();
}

bool MailQueue::isAvailableForInsert() const
{
    return m_isAvailableForInsert;
}

void MailQueue::setNotAvailableForInsert()
{
    m_isAvailableForInsert = false;
}
