#pragma once

class IMailSendCommand
{
public:
    virtual void send() = 0;
    virtual ~IMailSendCommand() = default;
};

typedef std::unique_ptr<IMailSendCommand> MailSendCommandPtr;