/*************************************************************
 * @file Mails.hpp
 * @author fishsaysblub (lj.vangastel@student.avans.nl)
 * @brief 
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
**************************************************************/

#include "Mails.h"
#include <stdlib.h>  
#include <stdio.h>  

/*************************************************************
 * @brief 
 * 
 * @tparam T 
 * @param Src 
 * @param Dst 
 * @param Size 
 * @return T* 
**************************************************************/
template<class T>
T* AllocateMail(uint8_t Src, uint8_t Dst, uint16_t Size) 
{
    MailEntryType* mail = (MailEntryType*)malloc(sizeof(MailEntryType));
    mail->Src = Src;
    mail->Dst = Dst;

    mail->Flags = 0x00;

    mail->Size = Size + OFFSETOF(MailEntryType, Mail);
    
    return reinterpret_cast<T*>(&mail->Mail);
}

template<class T>
uint16_t MailGetSize(T* Mail) 
{
    MailEntryType* entry = CONTAININGOFFSET(Mail, MailEntryType, Mail);
    return entry->Size;
}

template<class T>
uint16_t MailGetSrc(T* Mail) 
{
    MailEntryType* entry = CONTAININGOFFSET(Mail, MailEntryType, Mail);
    return entry->Src;
}

template<class T>
uint16_t MailGetDst(T* Mail) 
{
    MailEntryType* entry = CONTAININGOFFSET(Mail, MailEntryType, Mail);
    return entry->Dst;
}

template<class T>
void MailFree(T* Mail) 
{
    MailEntryType* entry = CONTAININGOFFSET(Mail, MailEntryType, Mail);
    delete entry;
}