#pragma once

class MailQueue;

class MailQueueConsumer
{
public:
    MailQueueConsumer(std::shared_ptr<MailQueue> const& queue);

    void consume();

private:
    std::shared_ptr<MailQueue> m_queue;
};

