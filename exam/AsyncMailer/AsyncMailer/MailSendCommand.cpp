#include "stdafx.h"
#include "MailSendCommand.h"
#include "Mail.h"

using namespace std;

MailSendCommand::MailSendCommand(unique_ptr<Mail> && mail)
    : m_mail(move(mail))
{}

void MailSendCommand::send()
{
    ofstream out(m_mail->recipient);
    out << m_mail->message << endl;
    out.close();
}