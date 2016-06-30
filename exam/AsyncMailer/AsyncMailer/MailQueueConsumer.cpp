#include "stdafx.h"
#include "MailQueueConsumer.h"
#include "MailQueue.h"

using namespace std;

MailQueueConsumer::MailQueueConsumer(shared_ptr<MailQueue> const& queue)
    : m_queue(queue)
{}

void MailQueueConsumer::consume()
{
    while (m_queue->isAvailableForInsert() || !m_queue->isEmpty())
    {
        auto mailCommand = m_queue->getSendMailCommand();
        if (mailCommand)
        {
            this_thread::sleep_for(5000ms);
            mailCommand->send();
        }
    }
}
