#ifndef __MAILS_H__
#define __MAILS_H__

#include <stdint.h>

/*!< Mail with byte array. */
#define OFFSETOF(type, field) ((uint32_t)(&((type*)0)->field))
#define CONTAININGOFFSET(address, type, field) ((type*)(void*)((uint8_t*)(address)-OFFSETOF(type, field)))


typedef enum
{
    /* Pi to MC*/
    GAME_INITIALIZE         = 0x00,
    GAME_START              = 0x01,
    GAME_STOP               = 0x02,
    GAME_RESET              = 0x03,
    GAME_HYBERNATE          = 0x04,

    /* MC to PI*/
    GAME_INITIALIZE_RESULT  = 0x50,
    GAME_START_RESULT       = 0x51,
    GAME_SETUP_RESULT       = 0x52,
    GAME_STOP_RESULT        = 0x53,
    GAME_RESET_RESULT       = 0x54,
    GAME_HYBERNATE_RESULT   = 0x55,
    GAME_COMPLETE           = 0x56,
    GAME_ERROR              = 0x57,
    
    /* Test cheats */
    GAME_FORCE_COMPLETE     = 0xF0,
} packed_MailPrimitives; typedef uint8_t MailPrimitive;

typedef enum
{
    SUCCESS                 = 0x00,
    FAILED                  = 0x01,
    DEVICE_FAILURE          = 0x02,
    GAME_HARDWARE_FAILURE   = 0x03 
} packed_MailStatus; typedef uint8_t MailStatus;

#pragma pack(push, 1)
typedef union Mail
{
    MailPrimitive Primitive;
    MailStatus status;
    uint8_t P1;
    uint8_t P2;
    uint8_t P3;
    uint8_t P4;
    uint8_t Data[0xFE]; /*!< Mail with byte array. */
    void* Align;        /*!< Dummy for struct alignment. */
} MailType;

typedef struct
{
    MailPrimitive Primitive;
    MailStatus status;
    uint8_t P1;
} MailP1Type;

typedef struct
{
    /* Required */
    MailPrimitive Primitive;
    MailStatus status;

    /* User definable */
    uint16_t KeyCode;

} KeyMailType;

typedef struct
{
    /* Required */
    MailPrimitive Primitive;
    MailStatus status;

    /* User definable */
    uint16_t length;
    uint8_t Data[1]; /*!< Max 0xFE */
} DataMailType;


typedef struct
{
    uint8_t Src;
    uint8_t Dst;
    uint8_t Flags;
    uint16_t Size;
    union 
    {
        MailType Mail;
    };
} MailEntryType;
#pragma pack(pop)

template<class T>
T* AllocateMail(uint8_t Src, uint8_t Dst, uint16_t Size);

template<class T>
uint16_t MailGetSize(const T* Mail);

template<class T>
uint16_t MailGetSrc(const T* Mail);

template<class T>
uint16_t MailGetDst(const T* Mail);

template<class T>
void MailFree(T* Mail);

#include <Mails.hpp>

#endif // __MAILS_H__