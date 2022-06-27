#include <I2C_Controller.h>
#include "Mails.h"
#include <Arduino.h>

template<class T>
void I2C_Controller::send_mail(T* Mail) 
{
    MailEntryType* entry = CONTAININGOFFSET(Mail, MailEntryType, Mail);

    // Handle sending through I2C;
    // Line below is due to crashing
    uint8_t dst = entry->Dst;
    
    Serial.print("Sending mail to: ");
    Serial.println(dst, HEX);

    start_mail_transmission(entry);

    MailFree(Mail);
}