#pragma once
#include "IMailSendCommand.h"

struct Mail;

class MailSendCommand : public IMailSendCommand
{
public:
    MailSendCommand(std::unique_ptr<Mail> && mail);

    void send() override;

private:
    std::unique_ptr<Mail> m_mail;

};

