#include <I2C_Controller.h>
#include "Mails.h"

#include <iostream>

template<class T>
void I2C_Controller::send_mail(T* Mail) 
{
    MailEntryType* entry = CONTAININGOFFSET(Mail, MailEntryType, Mail);

    start_mail_transmission(entry);

    MailFree(Mail);
}