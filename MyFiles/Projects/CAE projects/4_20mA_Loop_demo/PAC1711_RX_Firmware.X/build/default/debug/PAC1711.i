# 1 "PAC1711.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "PAC1711.c" 2
# 22 "PAC1711.c"
# 1 "./PAC1711.h" 1
# 31 "./PAC1711.h"
# 1 "./PAC1711_i2c.h" 1
# 48 "./PAC1711_i2c.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stddef.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stddef.h" 2 3
# 19 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stddef.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef long int wchar_t;
# 128 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned size_t;
# 138 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef int ptrdiff_t;
# 174 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 20 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stddef.h" 2 3
# 49 "./PAC1711_i2c.h" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 1 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned __int24 uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;
# 179 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;
# 215 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3
# 50 "./PAC1711_i2c.h" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdbool.h" 1 3
# 51 "./PAC1711_i2c.h" 2


# 1 "./mcc_generated_files/i2c_host/i2c1.h" 1
# 53 "./mcc_generated_files/i2c_host/i2c1.h"
# 1 "./mcc_generated_files/i2c_host/i2c_host_event_types.h" 1
# 39 "./mcc_generated_files/i2c_host/i2c_host_event_types.h"
# 1 "./mcc_generated_files/i2c_host/i2c_host_types.h" 1
# 44 "./mcc_generated_files/i2c_host/i2c_host_types.h"
typedef enum
{
    I2C_ERROR_NONE,
    I2C_ERROR_ADDR_NACK,
    I2C_ERROR_DATA_NACK,
    I2C_ERROR_BUS_COLLISION,
} i2c_host_error_t;
# 62 "./mcc_generated_files/i2c_host/i2c_host_types.h"
typedef struct i2c_transfer_setup
{
  uint32_t clkSpeed;
}i2c_host_transfer_setup_t;
# 40 "./mcc_generated_files/i2c_host/i2c_host_event_types.h" 2






typedef struct
{
    _Bool busy;
    uint16_t address;
    uint8_t *writePtr;
    size_t writeLength;
    uint8_t *readPtr;
    size_t readLength;
    _Bool switchToRead;
    i2c_host_error_t errorState;
} i2c_host_event_status_t;

extern volatile i2c_host_event_status_t i2c1Status;
# 54 "./mcc_generated_files/i2c_host/i2c1.h" 2
# 1 "./mcc_generated_files/i2c_host/i2c_host_interface.h" 1
# 48 "./mcc_generated_files/i2c_host/i2c_host_interface.h"
typedef struct
{
    void (*Initialize)(void);
    void (*Deinitialize)(void);
    _Bool (*Write)(uint16_t address, uint8_t *data, size_t dataLength);
    _Bool (*Read)(uint16_t address, uint8_t *data, size_t dataLength);
    _Bool (*WriteRead)(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength);
    _Bool (*TransferSetup)(struct i2c_transfer_setup* setup, uint32_t srcClkFreq);
    i2c_host_error_t (*ErrorGet)(void);
    _Bool (*IsBusy)(void);
    void (*CallbackRegister)(void (*callback)(void));
    void (*Tasks)(void);
}i2c_host_interface_t;
# 55 "./mcc_generated_files/i2c_host/i2c1.h" 2
# 79 "./mcc_generated_files/i2c_host/i2c1.h"
extern const i2c_host_interface_t I2C1_Host;
# 89 "./mcc_generated_files/i2c_host/i2c1.h"
void I2C1_Initialize(void);
# 98 "./mcc_generated_files/i2c_host/i2c1.h"
void I2C1_Deinitialize(void);
# 129 "./mcc_generated_files/i2c_host/i2c1.h"
_Bool I2C1_Write(uint16_t address, uint8_t *data, size_t dataLength);
# 160 "./mcc_generated_files/i2c_host/i2c1.h"
_Bool I2C1_Read(uint16_t address, uint8_t *data, size_t dataLength);
# 196 "./mcc_generated_files/i2c_host/i2c1.h"
_Bool I2C1_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength);
# 207 "./mcc_generated_files/i2c_host/i2c1.h"
i2c_host_error_t I2C1_ErrorGet(void);
# 217 "./mcc_generated_files/i2c_host/i2c1.h"
_Bool I2C1_IsBusy(void);
# 226 "./mcc_generated_files/i2c_host/i2c1.h"
void I2C1_CallbackRegister(void (*callbackHandler)(void));







void I2C1_ISR(void);







void I2C1_ERROR_ISR(void);







void I2C1_RX_ISR(void);







void I2C1_TX_ISR(void);
# 54 "./PAC1711_i2c.h" 2
# 99 "./PAC1711_i2c.h"
typedef enum
{

    PAC1711_I2C_TRANSFER_EVENT_PENDING = 0,

    PAC1711_I2C_TRANSFER_EVENT_COMPLETE = 1,


    PAC1711_I2C_TRANSFER_EVENT_HANDLE_EXPIRED = 2,

    PAC1711_I2C_TRANSFER_EVENT_ERROR = 3,
    PAC1711_I2C_TRANSFER_EVENT_HANDLE_INVALID = 4,

    PAC1711_I2C_TRANSFER_NO_EVENT = 100
} PAC1711_I2C_TRANSFER_EVENT, *PAC1711_I2C_TRANSFER_EVENT_P;
# 130 "./PAC1711_i2c.h"
typedef void ( *PAC1711_I2C_TRANSFER_EVENT_HANDLER_P )( PAC1711_I2C_TRANSFER_EVENT event, uintptr_t context );
# 157 "./PAC1711_i2c.h"
typedef _Bool (*DRV_I2C_WriteReadTransferAdd_P)(
        uint16_t,
        uint8_t*,
        size_t,
        uint8_t*,
        size_t
);
# 175 "./PAC1711_i2c.h"
typedef _Bool (*DRV_I2C_WriteTransferAdd_P)(
        uint16_t,
        uint8_t*,
        size_t
);
# 202 "./PAC1711_i2c.h"
typedef _Bool (* DRV_I2C_TransferStatusGet_P)(void);
# 218 "./PAC1711_i2c.h"
typedef void (*DRV_I2C_TransferEventHandler_P)(void);
typedef void (*DRV_I2C_TransferEventHandlerSet_P)(
               DRV_I2C_TransferEventHandler_P);
# 271 "./PAC1711_i2c.h"
typedef struct _PAC1711_I2C_INIT{
    uint16_t i2cAddress;







    DRV_I2C_WriteReadTransferAdd_P i2cWriteRead;

    DRV_I2C_WriteTransferAdd_P i2cWrite;



    DRV_I2C_TransferStatusGet_P i2cTransferStatusGet;

    DRV_I2C_TransferEventHandlerSet_P i2cTransferCallbackSet;

}PAC1711_I2C_INIT, *PAC1711_I2C_INIT_P;
# 341 "./PAC1711_i2c.h"
typedef struct _PAC1711_I2C_CONTEXT{
    uint16_t i2cAddress;
    PAC1711_I2C_TRANSFER_EVENT_HANDLER_P pi2cEventHandler;
    uintptr_t pi2cEventHandlerContext;
    _Bool i2cEventCallbackRegistered;






    DRV_I2C_WriteReadTransferAdd_P i2cWriteRead;

    DRV_I2C_WriteTransferAdd_P i2cWrite;



    DRV_I2C_TransferStatusGet_P i2cTransferStatusGet;

    DRV_I2C_TransferEventHandlerSet_P i2cTransferCallbackSet;

}PAC1711_I2C_CONTEXT, *PAC1711_I2C_CONTEXT_P;
# 412 "./PAC1711_i2c.h"
static __attribute__((inline)) _Bool PAC1711_I2C_Initialize( PAC1711_I2C_CONTEXT_P pi2c_context, PAC1711_I2C_INIT i2c_init){
    if( (pi2c_context == ((void*)0)) ||
        (i2c_init.i2cWriteRead == ((void*)0)) ||
        (i2c_init.i2cWrite == ((void*)0)) ) return 0;


    if( (i2c_init.i2cTransferStatusGet == ((void*)0)) && (i2c_init.i2cTransferCallbackSet == ((void*)0)) ) return 0;
# 434 "./PAC1711_i2c.h"
    pi2c_context->i2cAddress = i2c_init.i2cAddress;


    pi2c_context->i2cWriteRead = i2c_init.i2cWriteRead;
    pi2c_context->i2cWrite = i2c_init.i2cWrite;

    pi2c_context->i2cTransferStatusGet = i2c_init.i2cTransferStatusGet;
    pi2c_context->i2cTransferCallbackSet = i2c_init.i2cTransferCallbackSet;

    pi2c_context->i2cEventCallbackRegistered = 0;






    return 1;
}
# 467 "./PAC1711_i2c.h"
static __attribute__((inline)) PAC1711_I2C_TRANSFER_EVENT PAC1711_I2C_TransferStatusGet(PAC1711_I2C_CONTEXT i2c_context){
    i2c_host_error_t i2cError;
    if (i2c_context.i2cTransferStatusGet != ((void*)0)){
        if(i2c_context.i2cTransferStatusGet() == 0){

            i2cError = I2C1_ErrorGet();
            if (i2cError == I2C_ERROR_NONE){
                return PAC1711_I2C_TRANSFER_EVENT_COMPLETE;
            }else{
                return PAC1711_I2C_TRANSFER_EVENT_ERROR;
            }
        }else{
            return PAC1711_I2C_TRANSFER_EVENT_PENDING;
        }
    }else{
        return PAC1711_I2C_TRANSFER_NO_EVENT;
    }
}
# 507 "./PAC1711_i2c.h"
static __attribute__((inline)) _Bool PAC1711_I2C_WriteRead (
    PAC1711_I2C_CONTEXT_P pi2c_context,
    void* const writeBuffer,
    const size_t writeSize,
    void* const readBuffer,
    const size_t readSize)
{
    _Bool retcode = 1;
    retcode = ( pi2c_context->i2cWriteRead)(pi2c_context->i2cAddress,
                                                                               writeBuffer, writeSize,
                                                                               readBuffer, readSize);
    return retcode;
};
# 540 "./PAC1711_i2c.h"
static __attribute__((inline)) _Bool PAC1711_I2C_Write(
    PAC1711_I2C_CONTEXT_P pi2c_context,
    void* const writeBuffer,
    const size_t writeSize)
{
    _Bool retcode = 1;
    retcode = ( pi2c_context->i2cWrite)(pi2c_context->i2cAddress,
                                                                        writeBuffer, writeSize);
    return retcode;
}
# 568 "./PAC1711_i2c.h"
static __attribute__((inline)) void PAC1711_I2CDRV_EventHandler( void ){


    return;
}
# 594 "./PAC1711_i2c.h"
static __attribute__((inline)) _Bool PAC1711_I2C_TransferEventHandlerSet(
    const PAC1711_I2C_CONTEXT_P pi2c_context,
    const PAC1711_I2C_TRANSFER_EVENT_HANDLER_P eventHandler,
    const uintptr_t context
){
# 614 "./PAC1711_i2c.h"
    return 0;
}
# 32 "./PAC1711.h" 2
# 1 "./PAC1711_definitions.h" 1
# 172 "./PAC1711_definitions.h"
typedef struct _PAC1711_deviceID {
    uint8_t product;
    uint8_t manufacturer;
    uint8_t revision;
 } PAC1711_deviceID, *PAC1711_deviceID_P;





typedef struct _PAC1711_CONTROL_REGFIELDS{

    uint8_t SAMPLE_MODE : 4;
    uint8_t GPIO_ALERT1 : 2;
    uint8_t SLOW_ALERT0 : 2;

    uint8_t AVERAGE : 3;
    uint8_t AA : 1;
    uint8_t ACC_CONFIG : 2;
    uint8_t AUTO_REFRESH : 2;
} PAC1711_CONTROL_REGFIELDS, *PAC1711_CONTROL_REGFIELDS_P;
# 218 "./PAC1711_definitions.h"
typedef struct _PAC1711_SMBUS_SETTINGS_REGFIELDS {
    uint8_t GPIO_DATA1 : 1;
    uint8_t GPIO_DATA0 : 1;
    uint8_t ANY_ALERT : 1;
    uint8_t POR : 1;
    uint8_t TIMEOUT : 1;
    uint8_t BYTE_COUNT : 1;
    uint8_t : 1;
    uint8_t I2C_HISPEED : 1;
} PAC1711_SMBUS_SETTINGS_REGFIELDS, *PAC1711_SMBUS_SETTINGS_REGFIELDS_P;
# 244 "./PAC1711_definitions.h"
typedef struct _PAC1711_NEGPWRFSR_REGFIELDS {
    uint8_t CFG_VS : 2;
    uint8_t CFG_VB : 2;
} PAC1711_NEGPWRFSR_REGFIELDS, *PAC1711_NEGPWRFSR_REGFIELDS_P;
# 264 "./PAC1711_definitions.h"
typedef struct _PAC1711_SLOW_REGFIELDS {
    uint8_t Slow : 1;
    uint8_t SlowLowHigh : 1;
    uint8_t SlowHighLow : 1;
    uint8_t RefreshRise : 1;
    uint8_t RefreshVRise : 1;
    uint8_t RefreshFall : 1;
    uint8_t RefreshVFall : 1;
    uint8_t : 1;
} PAC1711_SLOW_REGFIELDS, *PAC1711_SLOW_REGFIELDS_P;
# 290 "./PAC1711_definitions.h"
typedef struct _PAC1711_ALERT_STATUS_REGFIELDS {

    uint8_t : 2;
    uint8_t RV : 1;
    uint8_t FV : 1;
    uint8_t RC : 1;
    uint8_t FC : 1;
    uint8_t OC : 1;
    uint8_t UC : 1;

    uint8_t OV : 1;
    uint8_t UV : 1;
    uint8_t OPC : 1;
    uint8_t OPW : 1;
    uint8_t ACC_OVF : 1;
    uint8_t ACC_COUNT : 1;
    uint8_t : 1;
    uint8_t : 1;
} PAC1711_ALERT_STATUS_REGFIELDS, *PAC1711_ALERT_STATUS_REGFIELDS_P;





typedef struct _PAC1711_ALERT_ENABLE_REGFIELDS {

    uint8_t : 2;
    uint8_t RV : 1;
    uint8_t FV : 1;
    uint8_t RC : 1;
    uint8_t FC : 1;
    uint8_t OC : 1;
    uint8_t UC : 1;

    uint8_t OV : 1;
    uint8_t UV : 1;
    uint8_t OPC : 1;
    uint8_t OPW : 1;
    uint8_t ACC_OVF : 1;
    uint8_t ACC_COUNT : 1;
    uint8_t ALERT_CCx : 1;
    uint8_t : 1;
} PAC1711_ALERT_ENABLE_REGFIELDS, *PAC1711_ALERT_ENABLE_REGFIELDS_P;
# 361 "./PAC1711_definitions.h"
typedef struct _PAC1711_ACCUM_LIMITS_REGFIELDS {
    uint8_t ACC_FULL : 6;
    uint8_t ACC_COUNT_FULL : 2;
} PAC1711_ACCUM_LIMITS_REGFIELDS, *PAC1711_ACCUM_LIMITS_REGFIELDS_P;
# 381 "./PAC1711_definitions.h"
typedef struct _PAC1711_STEP_LIMIT_REGFIELDS {
    uint8_t STEP_RV : 2;
    uint8_t STEP_FV : 2;
    uint8_t STEP_RC : 2;
    uint8_t STEP_FC : 2;
} PAC1711_STEP_LIMIT_REGFIELDS, *PAC1711_STEP_LIMIT_REGFIELDS_P;
# 405 "./PAC1711_definitions.h"
typedef struct _PAC1711_LIMIT_NSAMPLES_REGFIELDS {

    uint8_t : 2;
    uint8_t Nsamples_OPC : 2;
    uint8_t Nsamples_OPW : 2;

    uint8_t Nsamples_OC : 2;
    uint8_t Nsamples_UC : 2;
    uint8_t Nsamples_OV : 2;
    uint8_t Nsamples_UV : 2;
} PAC1711_LIMIT_NSAMPLES_REGFIELDS, *PAC1711_LIMIT_NSAMPLES_REGFIELDS_P;
# 33 "./PAC1711.h" 2
# 1 "./PAC1711_mutex.h" 1
# 50 "./PAC1711_mutex.h"
typedef uint8_t PAC1711_MUTEX;
# 61 "./PAC1711_mutex.h"
static __attribute__((inline)) _Bool PAC1711_MUTEX_Create(PAC1711_MUTEX *pmutex){
    return 1;
}
# 72 "./PAC1711_mutex.h"
static __attribute__((inline)) _Bool PAC1711_MUTEX_Lock(PAC1711_MUTEX *pmutex){
    return 1;
}






static __attribute__((inline)) void PAC1711_MUTEX_Unlock(PAC1711_MUTEX *pmutex){
    return;
}
# 34 "./PAC1711.h" 2







# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/string.h" 1 3
# 10 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/string.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/features.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/string.h" 2 3
# 25 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/string.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 1 3
# 421 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/string.h" 2 3

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);




char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 42 "./PAC1711.h" 2
# 103 "./PAC1711.h"
typedef struct _PAC1711_DEVICE_INIT{
    _Bool syncMode;


    uint32_t rsense;


    PAC1711_I2C_INIT i2c_init;

} PAC1711_DEVICE_INIT;






typedef enum {
    PAC1711_EVENT_NONE = -1,
    PAC1711_EVENT_REQUEST_SUCCESS = 0,
    PAC1711_EVENT_REQUEST_FAIL = 1,

    PAC1711_EVENT_REQUEST_ABORT = 2,

}PAC1711_EVENT, *PAC1711_EVENT_P;
# 141 "./PAC1711.h"
typedef void ( *PAC1711_EVENT_HANDLER )( PAC1711_EVENT event, uintptr_t context );







typedef enum _PAC1711_procState{
    Uninitialized = 0,
    Idle = 1,
    Sync = 2,

    RefreshReq = 10,
    GetDeviceIDReq = 20,
    SetRegisterReq = 30,
    GetRegister8bitReq = 40,
    GetRegister16bitReq = 50,
    GetRegister56bitReq = 60,
    GetRegister32bitReq = 70,

    GetCtrlRegisterReq = 80,
    GetCtrlLatRegisterReq = 81,
    SetCtrlRegisterReq = 85,
    GetNegPWRFSRRegisterReq = 90,
    GetNegPWRFSRLatRegisterReq = 91,
    SetNegPWRFSRRegisterReq = 95,
    GetSMBusRegisterReq = 100,
    SetSMBusRegisterReq = 110,
    GetSlowRegisterReq = 120,

    GetAccCountReq = 130,
    GetVACCValueReq = 140,
    GetVACCValueReq_polarityUpdate = 141,
    GetVACCValueReq_ctrlUpdate = 142,
    GetVACCValueReq_AccCntUpdate = 143,

    GetVBUSvalueReq = 150,
    GetVBUSValueReq_polarityUpdate = 151,

    GetVSENSEvalueReq = 160,
    GetVSENSEValueReq_polarityUpdate = 161,

    GetISENSEvalueReq = 170,
    GetISENSEValueReq_polarityUpdate = 171,

    GetVPOWERValueReq = 180,
    GetVPOWERValueReq_polarityUpdate = 181,

    GetAlertStatusRegisterReq = 200,
    GetAlertConfigRegisterReq = 210,
    GetAccFullnessRegisterReq = 220,
    GetLimitNsamplesRegisterReq = 230,
    GetCurrentLimitValueReq = 240,
    GetPowerLimitValueReq = 250,
    GetVoltageLimitValueReq = 260,
    GetStepLimitRegisterReq = 270,
} PAC1711_procState;
# 207 "./PAC1711.h"
typedef enum _PAC1711_ProcessMode{
    ProcessNone = 0,
    ProcessVACCget = 1,
    ProcessVACCenergy = 2,
    ProcessVACCcoulomb = 3,
    ProcessVACCtimedEnergy = 4,
    ProcessVACCtimedCoulomb = 5,
    ProcessCTRLlat = 6,
    ProcessNEGPWRlat = 7,
} PAC1711_ProcessMode;
# 231 "./PAC1711.h"
typedef struct _PAC1711_DEVICE_CONTEXT
{
    PAC1711_MUTEX mutexProcState;

    volatile PAC1711_procState processingState;
    PAC1711_EVENT deviceEventStatus;


    int16_t processError;






    PAC1711_I2C_CONTEXT i2c_context;
    volatile PAC1711_I2C_TRANSFER_EVENT i2cCommStatus;


    PAC1711_EVENT_HANDLER userCallback;

    uintptr_t userContext;


    _Bool syncMode;

    uint8_t i2cTxBuffer[3];
    uint8_t i2cRxBuffer[(7 + 1)];
    uint8_t i2cRxBuffer_ctrl[2 + 1];
    uint8_t i2cRxBuffer_negPwr[1 + 1];
    uint8_t i2cRxBuffer_accCount[4 + 1];

    _Bool is12bitADCres;
    uint16_t VbusMAX;
    uint16_t VsenseMAX;
    uint16_t VPowerMAX;

    uint32_t rsense;

    _Bool ENABLE_BYTE_COUNT_FLAG;





    uint16_t VbusScaleRange;
    uint16_t VsenseScaleRange;
    uint16_t VPowerScaleRange;
    _Bool IsSignedVbus;
    _Bool IsSignedVsense;
    _Bool IsSignedPower;


    PAC1711_deviceID deviceID;

    _Bool deviceID_cached;

    PAC1711_CONTROL_REGFIELDS ctrl_LAT;
    _Bool ctrl_LAT_cached;
    _Bool ctrl_change_pending;

    PAC1711_NEGPWRFSR_REGFIELDS negPwrFsr_LAT;
    _Bool negPwr_LAT_cached;
    _Bool negPwr_change_pending;

    uint32_t accCount;

    _Bool accCount_cached;

    PAC1711_ProcessMode regProcMode;

    uint32_t time;

    _Bool ABORT_REQUESTED_FLAG;

    void *outData;

    uint8_t *accMode;

} PAC1711_DEVICE_CONTEXT, *PAC1711_DEVICE_CONTEXT_P;
# 319 "./PAC1711.h"
typedef enum {
    PAC1711_REFRESH = 0,
    PAC1711_REFRESH_G = 1,
    PAC1711_REFRESH_V = 2
}PAC1711_REFRESH_MODE, *PAC1711_REFRESH_MODE_P;
# 354 "./PAC1711.h"
int16_t PAC1711_SetUserCallback(
    const PAC1711_DEVICE_CONTEXT_P pdevice,
    const PAC1711_EVENT_HANDLER userCallback,
    const uintptr_t userContext
);
# 382 "./PAC1711.h"
int16_t PAC1711_AbortRequest(PAC1711_DEVICE_CONTEXT_P pdevice);
# 405 "./PAC1711.h"
int16_t PAC1711_GetEventStatus(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_EVENT_P pevent, int16_t* pProcessError);
# 445 "./PAC1711.h"
int16_t PAC1711_Device_Initialize(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_DEVICE_INIT deviceInit);
# 463 "./PAC1711.h"
_Bool PAC1711_Device_IsInitialized(PAC1711_DEVICE_CONTEXT_P pdevice);
# 510 "./PAC1711.h"
int16_t PAC1711_GetDeviceID(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_deviceID_P pdeviceID);
# 553 "./PAC1711.h"
int16_t PAC1711_Refresh(PAC1711_DEVICE_CONTEXT_P pdevice);
# 597 "./PAC1711.h"
int16_t PAC1711_RefreshG(PAC1711_DEVICE_CONTEXT_P pdevice);
# 640 "./PAC1711.h"
int16_t PAC1711_RefreshV(PAC1711_DEVICE_CONTEXT_P pdevice);
# 687 "./PAC1711.h"
int16_t PAC1711_GetCtrl_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t reg_select, PAC1711_CONTROL_REGFIELDS_P pCtrl_reg);
# 728 "./PAC1711.h"
int16_t PAC1711_SetCtrl_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_CONTROL_REGFIELDS Ctrl_reg);
# 769 "./PAC1711.h"
int16_t PAC1711_GetAccumulatorCount(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val);
# 810 "./PAC1711.h"
int16_t PAC1711_GetAccumulatorCountPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 850 "./PAC1711.h"
int16_t PAC1711_SetAccumulatorCountPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val);
# 891 "./PAC1711.h"
int16_t PAC1711_GetVACC_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint64_t* pregister_val);
# 943 "./PAC1711.h"
int16_t PAC1711_GetVACC(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue, uint8_t* pmode);
# 984 "./PAC1711.h"
int16_t PAC1711_GetVACCPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1024 "./PAC1711.h"
int16_t PAC1711_SetVACCPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val);
# 1071 "./PAC1711.h"
int16_t PAC1711_GetEnergy_mWh(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1120 "./PAC1711.h"
int16_t PAC1711_GetTimedEnergy_mWh(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue, uint32_t time);
# 1167 "./PAC1711.h"
int16_t PAC1711_GetCoulomb_mAs(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1216 "./PAC1711.h"
int16_t PAC1711_GetTimedCoulomb_mAs(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue, uint32_t time);
# 1256 "./PAC1711.h"
int16_t PAC1711_GetVBUS_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1296 "./PAC1711.h"
int16_t PAC1711_GetVBUS_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1336 "./PAC1711.h"
int16_t PAC1711_GetVSENSE_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1377 "./PAC1711.h"
int16_t PAC1711_GetVSENSE_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1419 "./PAC1711.h"
int16_t PAC1711_GetISENSE_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1460 "./PAC1711.h"
int16_t PAC1711_GetVBUS_AVG_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1502 "./PAC1711.h"
int16_t PAC1711_GetVBUS_AVG_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1543 "./PAC1711.h"
int16_t PAC1711_GetVSENSE_AVG_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1585 "./PAC1711.h"
int16_t PAC1711_GetVSENSE_AVG_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1628 "./PAC1711.h"
int16_t PAC1711_GetISENSE_AVG_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1668 "./PAC1711.h"
int16_t PAC1711_GetVPOWER_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val);
# 1710 "./PAC1711.h"
int16_t PAC1711_GetVPOWER_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1750 "./PAC1711.h"
int16_t PAC1711_GetVBUSmin_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1791 "./PAC1711.h"
int16_t PAC1711_GetVBUSmin_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1831 "./PAC1711.h"
int16_t PAC1711_GetVBUSmax_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1872 "./PAC1711.h"
int16_t PAC1711_GetVBUSmax_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1912 "./PAC1711.h"
int16_t PAC1711_GetVSENSEmin_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 1953 "./PAC1711.h"
int16_t PAC1711_GetVSENSEmin_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 1993 "./PAC1711.h"
int16_t PAC1711_GetVSENSEmax_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 2034 "./PAC1711.h"
int16_t PAC1711_GetVSENSEmax_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 2076 "./PAC1711.h"
int16_t PAC1711_GetISENSEmin_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 2118 "./PAC1711.h"
int16_t PAC1711_GetISENSEmax_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 2159 "./PAC1711.h"
int16_t PAC1711_GetVPOWERmin_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val);
# 2201 "./PAC1711.h"
int16_t PAC1711_GetVPOWERmin_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 2242 "./PAC1711.h"
int16_t PAC1711_GetVPOWERmax_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val);
# 2284 "./PAC1711.h"
int16_t PAC1711_GetVPOWERmax_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 2325 "./PAC1711.h"
int16_t PAC1711_GetSMBusSettings_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SMBUS_SETTINGS_REGFIELDS_P pSMBus_reg);
# 2365 "./PAC1711.h"
int16_t PAC1711_SetSMBusSettings_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SMBUS_SETTINGS_REGFIELDS SMBus_reg);
# 2412 "./PAC1711.h"
int16_t PAC1711_GetNegPwrFsr_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t reg_select, PAC1711_NEGPWRFSR_REGFIELDS_P pNegPwrFsr_reg);
# 2453 "./PAC1711.h"
int16_t PAC1711_SetNegPwrFsr_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_NEGPWRFSR_REGFIELDS NegPwrFsr_reg);
# 2494 "./PAC1711.h"
int16_t PAC1711_GetSlow_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SLOW_REGFIELDS_P pSlow_reg);
# 2534 "./PAC1711.h"
int16_t PAC1711_SetSlow_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SLOW_REGFIELDS Slow_reg);
# 2575 "./PAC1711.h"
int16_t PAC1711_GetAlertStatus_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_STATUS_REGFIELDS_P pAlertStatus_reg);
# 2616 "./PAC1711.h"
int16_t PAC1711_GetAlertEnable_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS_P pAlertEnable_reg);
# 2658 "./PAC1711.h"
int16_t PAC1711_SetAlertEnable_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS AlertEnable_reg);
# 2699 "./PAC1711.h"
int16_t PAC1711_GetSlowAlert0_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS_P pSlowAlert0_reg);
# 2741 "./PAC1711.h"
int16_t PAC1711_SetSlowAlert0_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS AlertEnable_reg);
# 2782 "./PAC1711.h"
int16_t PAC1711_GetGpioAlert1_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS_P pGpioAlert1_reg);
# 2824 "./PAC1711.h"
int16_t PAC1711_SetGpioAlert1_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS AlertEnable_reg);
# 2865 "./PAC1711.h"
int16_t PAC1711_GetAccFullness_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ACCUM_LIMITS_REGFIELDS_P pAccFullnessLimits_reg);
# 2907 "./PAC1711.h"
int16_t PAC1711_SetAccFullness_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ACCUM_LIMITS_REGFIELDS AccFullnessLimits_reg);
# 2947 "./PAC1711.h"
int16_t PAC1711_GetOClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val);
# 2987 "./PAC1711.h"
int16_t PAC1711_SetOClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val);
# 3030 "./PAC1711.h"
int16_t PAC1711_GetOClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 3078 "./PAC1711.h"
int16_t PAC1711_SetOClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float value);
# 3118 "./PAC1711.h"
int16_t PAC1711_GetUClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val);
# 3158 "./PAC1711.h"
int16_t PAC1711_SetUClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val);
# 3201 "./PAC1711.h"
int16_t PAC1711_GetUClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 3249 "./PAC1711.h"
int16_t PAC1711_SetUClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float value);
# 3289 "./PAC1711.h"
int16_t PAC1711_GetOPWlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 3329 "./PAC1711.h"
int16_t PAC1711_GetOPClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val);
# 3369 "./PAC1711.h"
int16_t PAC1711_SetOPWlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val);
# 3409 "./PAC1711.h"
int16_t PAC1711_SetOPClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val);
# 3452 "./PAC1711.h"
int16_t PAC1711_GetOPWlimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 3495 "./PAC1711.h"
int16_t PAC1711_GetOPClimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 3543 "./PAC1711.h"
int16_t PAC1711_SetOPWlimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float value);
# 3591 "./PAC1711.h"
int16_t PAC1711_SetOPClimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float value);
# 3631 "./PAC1711.h"
int16_t PAC1711_GetOVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val);
# 3671 "./PAC1711.h"
int16_t PAC1711_SetOVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val);
# 3712 "./PAC1711.h"
int16_t PAC1711_GetOVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 3757 "./PAC1711.h"
int16_t PAC1711_SetOVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float value);
# 3797 "./PAC1711.h"
int16_t PAC1711_GetUVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val);
# 3837 "./PAC1711.h"
int16_t PAC1711_SetUVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val);
# 3878 "./PAC1711.h"
int16_t PAC1711_GetUVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue);
# 3923 "./PAC1711.h"
int16_t PAC1711_SetUVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float value);
# 3967 "./PAC1711.h"
int16_t PAC1711_GetStepLimit(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_STEP_LIMIT_REGFIELDS_P pStepLimit_reg);
# 4011 "./PAC1711.h"
int16_t PAC1711_SetStepLimit(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_STEP_LIMIT_REGFIELDS StepLimit_reg);
# 4054 "./PAC1711.h"
int16_t PAC1711_GetLimitNsamples(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_LIMIT_NSAMPLES_REGFIELDS_P pLimitNsamples_reg);
# 4097 "./PAC1711.h"
int16_t PAC1711_SetLimitNsamples(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_LIMIT_NSAMPLES_REGFIELDS LimitNsamples_reg);
# 4116 "./PAC1711.h"
_Bool PAC1711_Device_IsBusy(PAC1711_DEVICE_CONTEXT_P pdevice);
# 4162 "./PAC1711.h"
int16_t PAC1711_LibTask(PAC1711_DEVICE_CONTEXT_P pdevice);
# 4185 "./PAC1711.h"
int16_t PAC1711_DecodeCTRLtoSampleRate(PAC1711_CONTROL_REGFIELDS ctrlReg);
# 4208 "./PAC1711.h"
void PAC1711_Reg16bitToRawBytes(uint16_t regVal, uint8_t* pRawBytes);
# 4232 "./PAC1711.h"
uint16_t PAC1711_RawBytestoReg16bit(uint8_t* pRawBytes);
# 4256 "./PAC1711.h"
uint32_t PAC1711_RawBytestoReg32bit(uint8_t* pRawBytes);
# 4280 "./PAC1711.h"
uint64_t PAC1711_RawBytesToReg64bit(uint8_t* pRawBytes);
# 4307 "./PAC1711.h"
void PAC1711_CtrlBytesToRegfields(uint8_t* pCtrlBytes, PAC1711_CONTROL_REGFIELDS_P pCtrlRegfields);
# 4333 "./PAC1711.h"
void PAC1711_CtrlRegfieldsToBytes(PAC1711_CONTROL_REGFIELDS CtrlRegfields, uint8_t* pCtrlBytes);
# 4360 "./PAC1711.h"
void PAC1711_NegPwrFsrBytesToRegfields(uint8_t* pNegPwrFsrBytes, PAC1711_NEGPWRFSR_REGFIELDS_P pNegPwrFsrRegfields);
# 4386 "./PAC1711.h"
void PAC1711_NegPwrFsrRegfieldsToBytes(PAC1711_NEGPWRFSR_REGFIELDS NegPwrFsrRegfields, uint8_t* pNegPwrFsrBytes);
# 4413 "./PAC1711.h"
void PAC1711_SMBusBytesToRegfields(uint8_t* pSMBusBytes, PAC1711_SMBUS_SETTINGS_REGFIELDS_P pSMBusRegfields);
# 4439 "./PAC1711.h"
void PAC1711_SMBusRegfieldsToBytes(PAC1711_SMBUS_SETTINGS_REGFIELDS SMBusRegfields, uint8_t* pSMBusBytes);
# 4466 "./PAC1711.h"
void PAC1711_SlowBytesToRegfields(uint8_t* pSlowBytes, PAC1711_SLOW_REGFIELDS_P pSlowRegfields);
# 4492 "./PAC1711.h"
void PAC1711_SlowRegfieldsToBytes(PAC1711_SLOW_REGFIELDS SlowRegfields, uint8_t* pSlowBytes);
# 4519 "./PAC1711.h"
void PAC1711_AlertStatusBytesToRegfields(uint8_t* pAlertBytes, PAC1711_ALERT_STATUS_REGFIELDS_P pAlertStatusRegfields);
# 4546 "./PAC1711.h"
void PAC1711_AlertEnableBytesToRegfields(uint8_t* pAlertBytes, PAC1711_ALERT_ENABLE_REGFIELDS_P pAlertEnableRegfields);
# 4572 "./PAC1711.h"
void PAC1711_AlertEnableRegfieldsToBytes(PAC1711_ALERT_ENABLE_REGFIELDS AlertEnableRegfields, uint8_t* pAlertBytes);
# 4599 "./PAC1711.h"
void PAC1711_AccFullnessBytesToRegfields(uint8_t* pAccFullnessBytes, PAC1711_ACCUM_LIMITS_REGFIELDS_P pAccFullnessRegfields);
# 4625 "./PAC1711.h"
void PAC1711_AccFullnessRegfieldsToBytes(PAC1711_ACCUM_LIMITS_REGFIELDS AccFullnessRegfields, uint8_t* pAccFullnessBytes);
# 4651 "./PAC1711.h"
void PAC1711_StepLimitBytesToRegfields(uint8_t* pStepLimitBytes, PAC1711_STEP_LIMIT_REGFIELDS_P pStepLimitRegfields);
# 4677 "./PAC1711.h"
void PAC1711_StepLimitRegfieldsToBytes(PAC1711_STEP_LIMIT_REGFIELDS StepLimitRegfields, uint8_t* pStepLimitBytes);
# 4703 "./PAC1711.h"
void PAC1711_NsamplesBytesToRegfields(uint8_t* pNsamplesBytes, PAC1711_LIMIT_NSAMPLES_REGFIELDS_P pNsamplesRegfields);
# 4729 "./PAC1711.h"
void PAC1711_NsamplesRegfieldsToBytes(PAC1711_LIMIT_NSAMPLES_REGFIELDS NsamplesRegfields, uint8_t* pNsamplesBytes);
# 4753 "./PAC1711.h"
_Bool PAC1711_IsSignedVbus(PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr);
# 4777 "./PAC1711.h"
_Bool PAC1711_IsSignedVsense(PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr);
# 4801 "./PAC1711.h"
_Bool PAC1711_IsSignedVpower(PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr);
# 4826 "./PAC1711.h"
uint16_t PAC1711_VbusScaleRange(uint16_t VbusMAX, PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr);
# 4852 "./PAC1711.h"
uint16_t PAC1711_VsenseScaleRange(uint16_t VsenseMax, PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr);
# 4878 "./PAC1711.h"
uint16_t PAC1711_VpowerScaleRange(uint16_t VPowerMax, PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr);
# 4924 "./PAC1711.h"
float PAC1711_VaccReg64bitToVoltage_mV(uint64_t VAccReg, _Bool IsSignedVoltage, uint16_t VoltageScaleRange, _Bool is12bitADCres);
# 4960 "./PAC1711.h"
float PAC1711_VaccReg64bitToPower_mW(uint64_t VAccReg, _Bool IsSignedPower, uint16_t VPowerScaleRange, _Bool is12bitADCres, uint32_t rsense);
# 4992 "./PAC1711.h"
float PAC1711_VpowerReg32bitToPower_mW(uint32_t VpowerReg, _Bool IsSignedPower, uint16_t VPowerScaleRange, uint32_t rsense);
# 5021 "./PAC1711.h"
float PAC1711_VoltageReg16bitToVoltage_mV(uint16_t VoltageReg, _Bool IsSignedVoltage, uint16_t VoltageScaleRange);
# 5051 "./PAC1711.h"
float PAC1711_VoltageReg16bitToCurrent_mA(uint16_t VsenseReg, _Bool IsSignedVoltage, uint16_t VsenseScaleRange, uint32_t rsense);
# 5079 "./PAC1711.h"
float PAC1711_VaccPowerToEnergy_mWh(float accumulatedPower_mW, int16_t sampleRate);
# 5106 "./PAC1711.h"
float PAC1711_VaccPowerTimedToEnergy_mWh(float accumulatedPower_mW, uint32_t sampleCount, uint32_t time_ms);
# 5135 "./PAC1711.h"
float PAC1711_VaccVoltageToCoulombCnt(float accumulatedVoltage_mV, int16_t sampleRate, uint32_t rsense);
# 5164 "./PAC1711.h"
float PAC1711_VaccVoltageTimedToCoulombCnt(float accumulatedVoltage_mV, uint32_t sampleCount, uint32_t time_ms, uint32_t rsense);
# 5186 "./PAC1711.h"
float PAC1711_CLimitRegisterToCurrent_mA(uint8_t limitRegister, uint16_t VsenseMAX, uint32_t rsense);
# 5209 "./PAC1711.h"
float PAC1711_PLimitRegisterToPower_mW(uint16_t limitRegister, uint16_t VPowerMAX, uint32_t rsense);
# 5229 "./PAC1711.h"
float PAC1711_VLimitRegisterToVoltage_mV(uint8_t limitRegister, uint16_t VbusMAX);
# 5256 "./PAC1711.h"
uint16_t PAC1711_Plimit_mWtoRegisterVal(float PowerLimit, uint16_t VPowerMAX, uint32_t rsense);
# 5283 "./PAC1711.h"
uint8_t PAC1711_Climit_mAtoRegisterVal(float CurrentLimit, uint16_t VsenseMAX, uint32_t rsense);
# 5308 "./PAC1711.h"
uint8_t PAC1711_Vlimit_mVtoRegisterVal(float VoltageLimit, uint16_t VbusMax);
# 23 "PAC1711.c" 2





void PAC1711_I2CEventHandler(PAC1711_I2C_TRANSFER_EVENT event, uintptr_t context);

static void PAC1711_GetDeviceIDProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetCtrl_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ProcessMode procMode);
static void PAC1711_GetAccumulatorCountProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static int16_t PAC1711_GetVACCProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetVBUS_mVProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetVSENSE_mVProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetISENSE_mAProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetVPOWER_mWProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetSMBusSettings_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_SetSMBusSettings_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetNegPwrFsr_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ProcessMode procMode);
static void PAC1711_GetSlow_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetAlertStatus_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetAlert_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetAccFullness_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetCurrentLimit_mAProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetPowerLimit_mWProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetVoltageLimit_mVProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetStepLimitProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_GetLimitNsamplesProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static int16_t PAC1711_UpdateContext_ChannelPolarity(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_UpdateContext_ChannelPolarityProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static int16_t PAC1711_UpdateContext_Ctrl(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_UpdateContext_CtrlProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static int16_t PAC1711_UpdateContext_AccumulatorCount(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_UpdateContext_AccumulatorCountProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static int16_t PAC1711_Get_Register(PAC1711_DEVICE_CONTEXT_P pdevice,
                                    void* pregister_val, uint8_t registerAddr, size_t regSize,
                                    PAC1711_procState processingState);
static int16_t PAC1711_Get_VACCRegister(PAC1711_DEVICE_CONTEXT_P pdevice,
                                        void* pregister_val, uint8_t* pmode, uint32_t time,
                                        PAC1711_ProcessMode procMode);
static void PAC1711_Get_Reg8bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_Get_Reg16bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_Get_Reg32bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static void PAC1711_Get_Reg56bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice);
static int16_t PAC1711_Set_Register(PAC1711_DEVICE_CONTEXT_P pdevice,
                                    uint8_t *pregisterBytes, uint8_t registerAddr, size_t regSize,
                                    PAC1711_procState processingState);

static __attribute__((inline)) void PAC1711_UpdateContext_ScaleValues(PAC1711_DEVICE_CONTEXT_P pdevice);






int16_t PAC1711_AbortRequest(PAC1711_DEVICE_CONTEXT_P pdevice){
    if (pdevice != ((void*)0)){
        pdevice->ABORT_REQUESTED_FLAG = 1;
        return 0;
    }else{
        return 6;
    }
}

static void __attribute__((inline)) callUserCallback(PAC1711_DEVICE_CONTEXT_P pdevice){

    if(pdevice->userCallback != ((void*)0)){
        PAC1711_EVENT_HANDLER userCallback;
        PAC1711_EVENT event;
        uintptr_t userContext;

        userCallback = pdevice->userCallback;
        event = pdevice->deviceEventStatus;
        userContext = pdevice->userContext;
        userCallback(event, userContext);
    }
}



void PAC1711_I2CEventHandler(PAC1711_I2C_TRANSFER_EVENT event, uintptr_t pdevice_context)
{
    if(pdevice_context == 0){
        return;
    }
    switch(event){
        case PAC1711_I2C_TRANSFER_EVENT_HANDLE_EXPIRED:
        case PAC1711_I2C_TRANSFER_EVENT_ERROR:
        case PAC1711_I2C_TRANSFER_EVENT_HANDLE_INVALID:
            ((PAC1711_DEVICE_CONTEXT_P)pdevice_context)->i2cCommStatus = PAC1711_I2C_TRANSFER_EVENT_ERROR;
            break;
        default:
            ((PAC1711_DEVICE_CONTEXT_P)pdevice_context)->i2cCommStatus = event;
    }
}


static void RequestCompletion(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_EVENT deviceEvent, int16_t errorCode){
    pdevice->deviceEventStatus = deviceEvent;
    pdevice->processError = errorCode;

    callUserCallback(pdevice);
    if ( pdevice->syncMode == 1){
        pdevice->processingState = Sync;
    }else{
        pdevice->processingState = Idle;
    }
}

int16_t PAC1711_LibTask(PAC1711_DEVICE_CONTEXT_P pdevice)
{
    int16_t errorCode = 0;
    PAC1711_EVENT libEvent;

    if(pdevice == ((void*)0)) return 12;

    switch(pdevice->processingState){
        case Sync:
            if ( pdevice->syncMode != 1) pdevice->processingState = Idle;
        case Idle:
        case Uninitialized:
            pdevice->ABORT_REQUESTED_FLAG = 0;
            return 0;
        default:
            break;
    }


    if(pdevice->ABORT_REQUESTED_FLAG == 1){
        pdevice->ABORT_REQUESTED_FLAG = 0;
        RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_ABORT, 2);
        return 0;
    }

    if(pdevice->i2c_context.i2cEventCallbackRegistered == 0){


        PAC1711_I2C_TRANSFER_EVENT i2cEvent;
        i2cEvent = PAC1711_I2C_TransferStatusGet(pdevice->i2c_context);
        PAC1711_I2CEventHandler(i2cEvent, (uintptr_t)pdevice);
    }



    if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_ERROR){
        RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, 4);
        return 0;
    }


    switch(pdevice->processingState)
    {
        case RefreshReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetDeviceIDReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetDeviceIDProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;



        case GetRegister8bitReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_Get_Reg8bitProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;




        case GetRegister16bitReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_Get_Reg16bitProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;



        case GetRegister32bitReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_Get_Reg32bitProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;


        case GetRegister56bitReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_Get_Reg56bitProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetCtrlRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetCtrl_regProcess(pdevice, ProcessNone);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetCtrlLatRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetCtrl_regProcess(pdevice, ProcessCTRLlat);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetSMBusRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetSMBusSettings_regProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetNegPWRFSRRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetNegPwrFsr_regProcess(pdevice, ProcessNone);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetNegPWRFSRLatRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetNegPwrFsr_regProcess(pdevice, ProcessNEGPWRlat);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetAccCountReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetAccumulatorCountProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetSlowRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetSlow_regProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetAlertStatusRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetAlertStatus_regProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;



        case GetAlertConfigRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetAlert_regProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetAccFullnessRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetAccFullness_regProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetStepLimitRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetStepLimitProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case GetLimitNsamplesRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetLimitNsamplesProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;






        case SetRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case SetCtrlRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                pdevice->ctrl_change_pending = 1;

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case SetNegPWRFSRRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                pdevice->negPwr_change_pending = 1;

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;

        case SetSMBusRegisterReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_SetSMBusSettings_regProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;



        case GetCurrentLimitValueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetCurrentLimit_mAProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;



        case GetPowerLimitValueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetPowerLimit_mWProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;



        case GetVoltageLimitValueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){
                PAC1711_GetVoltageLimit_mVProcess(pdevice);

                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            }
            return 0;



        case GetVBUSvalueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){


                errorCode = PAC1711_UpdateContext_ChannelPolarity(pdevice);
                if ((errorCode != 0) &&
                    (errorCode != 1000)){
                    RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, errorCode);
                    return 0;
                }
                pdevice->processingState = GetVBUSValueReq_polarityUpdate;
            }else{
                return 0;
            }
        case GetVBUSValueReq_polarityUpdate:
            if(errorCode != 1000){
                if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                    PAC1711_UpdateContext_ChannelPolarityProcess(pdevice);
                }else{
                    return 0;
                }
            }
            PAC1711_GetVBUS_mVProcess(pdevice);

            RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            return 0;



        case GetVSENSEvalueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){


                errorCode = PAC1711_UpdateContext_ChannelPolarity(pdevice);
                if ((errorCode != 0) &&
                    (errorCode != 1000)){
                    RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, errorCode);
                    return 0;
                }
                pdevice->processingState = GetVSENSEValueReq_polarityUpdate;
            }else{
                return 0;
            }
        case GetVSENSEValueReq_polarityUpdate:
            if(errorCode != 1000){
                if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                    PAC1711_UpdateContext_ChannelPolarityProcess(pdevice);
                }else{
                    return 0;
                }
            }
            PAC1711_GetVSENSE_mVProcess(pdevice);

            RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            return 0;



        case GetISENSEvalueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){


                errorCode = PAC1711_UpdateContext_ChannelPolarity(pdevice);
                if ((errorCode != 0) &&
                    (errorCode != 1000)){
                    RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, errorCode);
                    return 0;
                }
                pdevice->processingState = GetISENSEValueReq_polarityUpdate;
            }else{
                return 0;
            }
        case GetISENSEValueReq_polarityUpdate:
            if(errorCode != 1000){
                if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                    PAC1711_UpdateContext_ChannelPolarityProcess(pdevice);
                }else{
                    return 0;
                }
            }
            PAC1711_GetISENSE_mAProcess(pdevice);

            RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            return 0;



        case GetVPOWERValueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){


                errorCode = PAC1711_UpdateContext_ChannelPolarity(pdevice);
                if ((errorCode != 0) &&
                    (errorCode != 1000)){
                    RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, errorCode);
                    return 0;
                }
                pdevice->processingState = GetVPOWERValueReq_polarityUpdate;
            }else{
                return 0;
            }
        case GetVPOWERValueReq_polarityUpdate:
            if(errorCode != 1000){
                if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                    PAC1711_UpdateContext_ChannelPolarityProcess(pdevice);
                }else{
                    return 0;
                }
            }
            PAC1711_GetVPOWER_mWProcess(pdevice);

            RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_SUCCESS, 0);
            return 0;






        case GetVACCValueReq:
            if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){


                errorCode = PAC1711_UpdateContext_ChannelPolarity(pdevice);
                if ((errorCode != 0) &&
                    (errorCode != 1000)){
                    RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, errorCode);
                    return 0;
                }
                pdevice->processingState = GetVACCValueReq_polarityUpdate;
            }else{
                return 0;
            }
        case GetVACCValueReq_polarityUpdate:
            if(errorCode != 1000){
                if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                    PAC1711_UpdateContext_ChannelPolarityProcess(pdevice);
                }else{
                    return 0;
                }
            }
            errorCode = PAC1711_UpdateContext_Ctrl((PAC1711_DEVICE_CONTEXT_P)pdevice);
            if ((errorCode != 0) &&
                (errorCode != 1000)){
                RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, errorCode);
                return 0;
            }
            pdevice->processingState = GetVACCValueReq_ctrlUpdate;
        case GetVACCValueReq_ctrlUpdate:
            if(errorCode != 1000){
                if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                    PAC1711_UpdateContext_CtrlProcess(pdevice);
                }else{
                    return 0;
                }
            }
            if((pdevice->regProcMode == ProcessVACCtimedEnergy) ||
               (pdevice->regProcMode == ProcessVACCtimedCoulomb) ){

                errorCode = PAC1711_UpdateContext_AccumulatorCount(pdevice);
                if ((errorCode != 0) &&
                    (errorCode != 1000)){
                    RequestCompletion(pdevice, PAC1711_EVENT_REQUEST_FAIL, errorCode);
                    return 0;
                }
            }
            pdevice->processingState = GetVACCValueReq_AccCntUpdate;
        case GetVACCValueReq_AccCntUpdate:
            if((pdevice->regProcMode == ProcessVACCtimedEnergy) ||
               (pdevice->regProcMode == ProcessVACCtimedCoulomb) ){
                if(errorCode != 1000){
                    if(pdevice->i2cCommStatus == PAC1711_I2C_TRANSFER_EVENT_COMPLETE){

                        PAC1711_UpdateContext_AccumulatorCountProcess(pdevice);
                    }else{
                        return 0;
                    }
                }
            }

            errorCode = PAC1711_GetVACCProcess(pdevice);
            if (errorCode != 0){
                libEvent = PAC1711_EVENT_REQUEST_FAIL;
            }else{

                libEvent = PAC1711_EVENT_REQUEST_SUCCESS;
            }
            RequestCompletion(pdevice, libEvent, errorCode);
            return 0;

        default:
            return 0;
    }
}


_Bool PAC1711_Device_IsInitialized(PAC1711_DEVICE_CONTEXT_P pdevice){
    if (pdevice == ((void*)0)){
        return 0;
    }else{
        return (pdevice->processingState != Uninitialized);
    }
}


_Bool PAC1711_Device_IsBusy(PAC1711_DEVICE_CONTEXT_P pdevice){
    _Bool deviceIsBusy = 0;
    if (pdevice != ((void*)0)){
        if( pdevice->processingState != Idle ) deviceIsBusy = 1;
    }
    return deviceIsBusy;
}


int16_t PAC1711_Device_Initialize(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_DEVICE_INIT deviceInit) {
    int16_t errorCode = 0;

    if (pdevice == ((void*)0)) return 6;


    memset(pdevice, 0, sizeof(PAC1711_DEVICE_CONTEXT));


    if( PAC1711_MUTEX_Create(&(pdevice->mutexProcState)) == 0 )
    {
        return 5;
    }


    if( PAC1711_MUTEX_Lock(&(pdevice->mutexProcState)) == 0 )
    {
        return 1;
    }

    pdevice->processingState = Uninitialized;
    pdevice->deviceEventStatus = PAC1711_EVENT_NONE;
    pdevice->ABORT_REQUESTED_FLAG = 0;


    if (0 == PAC1711_I2C_Initialize(&(pdevice->i2c_context), deviceInit.i2c_init)){
        pdevice->processError = 4;
        errorCode = 4;
        goto initialize_error;
    }

    if(0 == PAC1711_I2C_TransferEventHandlerSet(&(pdevice->i2c_context),
                                                    PAC1711_I2CEventHandler,
                                                    (uintptr_t)pdevice)){
        pdevice->i2c_context.i2cEventCallbackRegistered = 0;
    }else{
        pdevice->i2c_context.i2cEventCallbackRegistered = 1;
    }





    pdevice->syncMode = 1;
    pdevice->processingState = Idle;


    PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));

    pdevice->ENABLE_BYTE_COUNT_FLAG = 0;

    pdevice->deviceID_cached = 0;
    pdevice->negPwr_change_pending = 0;
    pdevice->negPwr_LAT_cached = 0;
    pdevice->ctrl_change_pending = 0;
    pdevice->ctrl_LAT_cached = 0;
    pdevice->accCount_cached = 0;



    PAC1711_SMBUS_SETTINGS_REGFIELDS SMBus;
    SMBus.GPIO_DATA1 = 0b0;
    SMBus.GPIO_DATA0 = 0b0;
    SMBus.ANY_ALERT = 0b0;
    SMBus.POR = 0b1;
    SMBus.TIMEOUT = 0b0;
    SMBus.BYTE_COUNT = 0b0;
    SMBus.I2C_HISPEED = 0b0;
    errorCode = PAC1711_SetSMBusSettings_reg(pdevice, SMBus);
    if(errorCode != 0) goto initialize_error;


    errorCode = PAC1711_GetDeviceID(pdevice, &(pdevice->deviceID));
    if(errorCode != 0) goto initialize_error;


    pdevice->VsenseMAX = 100;

    switch (pdevice->deviceID.product){


        case 0x88:{
            pdevice->is12bitADCres = 1;
            pdevice->VbusMAX = 42000;
            pdevice->VPowerMAX = 4200;
            break;
        }
        case 0x80:{
            pdevice->is12bitADCres = 1;
            pdevice->VbusMAX = 42000;
            pdevice->VPowerMAX = 4200;
            break;
        }
        case 0x89:{
            pdevice->is12bitADCres = 1;
            pdevice->VbusMAX = 9000;
            pdevice->VPowerMAX = 900;
            break;
        }
        case 0x81:{
            pdevice->is12bitADCres = 1;
            pdevice->VbusMAX = 9000;
            pdevice->VPowerMAX = 900;
            break;
        }
        case 0x82:{
            pdevice->is12bitADCres = 1;
            pdevice->VbusMAX = 65000;
            pdevice->VPowerMAX = 6500;
            break;
        }


        case 0x8C:{
            pdevice->is12bitADCres = 0;
            pdevice->VbusMAX = 42000;
            pdevice->VPowerMAX = 4200;
            break;
        }
        case 0x84:{
            pdevice->is12bitADCres = 0;
            pdevice->VbusMAX = 42000;
            pdevice->VPowerMAX = 4200;
            break;
        }
        case 0x8D:{
            pdevice->is12bitADCres = 0;
            pdevice->VbusMAX = 9000;
            pdevice->VPowerMAX = 900;
            break;
        }
        case 0x85:{
            pdevice->is12bitADCres = 0;
            pdevice->VbusMAX = 9000;
            pdevice->VPowerMAX = 900;
            break;
        }
        case 0x86:{
            pdevice->is12bitADCres = 0;
            pdevice->VbusMAX = 65000;
            pdevice->VPowerMAX = 6500;
            break;
        }

        default:
            errorCode = 8;
            goto initialize_error;
    }
    pdevice->deviceID_cached = 1;

    pdevice->rsense = deviceInit.rsense;
# 794 "PAC1711.c"
    PAC1711_CONTROL_REGFIELDS Ctrl;
    Ctrl.SAMPLE_MODE = 0b0011;
    Ctrl.GPIO_ALERT1 = 0b01;
    Ctrl.SLOW_ALERT0 = 0b01;
    Ctrl.AVERAGE = 0b001;
    Ctrl.AA = 0b0;
    Ctrl.ACC_CONFIG = 0b00;
    Ctrl.AUTO_REFRESH = 0b00;
    errorCode = PAC1711_SetCtrl_reg(pdevice, Ctrl);
    if(errorCode != 0) goto initialize_error;



    PAC1711_NEGPWRFSR_REGFIELDS NegPwr = {0};
    NegPwr.CFG_VS = 0b00 ;
    NegPwr.CFG_VB = 0b00 ;
    errorCode = PAC1711_SetNegPwrFsr_reg(pdevice, NegPwr);
    if(errorCode != 0) goto initialize_error;



    PAC1711_SLOW_REGFIELDS Slow = {0};
    Slow.RefreshRise = 0b0;
    Slow.RefreshVRise = 0b0;
    Slow.RefreshFall = 0b0;
    Slow.RefreshVFall = 0b0;
    errorCode = PAC1711_SetSlow_reg(pdevice, Slow);
    if(errorCode != 0) goto initialize_error;


    PAC1711_ACCUM_LIMITS_REGFIELDS AccLimits;
    AccLimits.ACC_COUNT_FULL = 0b01;
    errorCode = PAC1711_SetAccFullness_reg(pdevice, AccLimits);
    if(errorCode != 0) goto initialize_error;


    PAC1711_ALERT_ENABLE_REGFIELDS AlertEnable;
    memset(&AlertEnable, 0, sizeof(PAC1711_ALERT_ENABLE_REGFIELDS));
    errorCode = PAC1711_SetAlertEnable_reg(pdevice, AlertEnable);
    if(errorCode != 0) goto initialize_error;

    errorCode = PAC1711_Refresh(pdevice);



initialize_error:
    if(errorCode != 0){
        pdevice->processingState = Uninitialized;
    }
    pdevice->syncMode = deviceInit.syncMode;
    PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
    return errorCode;
}


int16_t PAC1711_SetUserCallback(
    const PAC1711_DEVICE_CONTEXT_P pdevice,
    const PAC1711_EVENT_HANDLER userCallback,
    const uintptr_t userContext
){
    if( (pdevice == ((void*)0)) || (userCallback == ((void*)0)) ){
        return 6;
    }



    if( PAC1711_MUTEX_Lock(&(pdevice->mutexProcState)) == 0 )
    {
        return 1;
    }

    if(pdevice->processingState == Idle){

        pdevice->userCallback = userCallback;
        pdevice->userContext = userContext;
        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
        return 0;
    }else
    {

        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
        return 1;
    }
}

int16_t PAC1711_GetEventStatus(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_EVENT_P pevent, int16_t* pProcessError){
    if ( (pdevice == ((void*)0)) || (pevent == ((void*)0)) || (pProcessError == ((void*)0)) ) return 6;
    *pevent = pdevice->deviceEventStatus;
    *pProcessError = pdevice->processError;
    return 0;
}

static int16_t RequestReturn(PAC1711_DEVICE_CONTEXT_P pdevice){

    int16_t retcode = 3;
    if(pdevice->syncMode == 1){
        while (pdevice->processingState != Sync){
            if (PAC1711_LibTask(pdevice) == 12){
                return 12;
            }
        }
        retcode = pdevice->processError;
        pdevice->processingState = Idle;
    }
    return retcode;
}

int16_t PAC1711_GetDeviceID(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_deviceID_P pdeviceID){
    int16_t retcode;
    _Bool bSuccess;
    if ((pdevice == ((void*)0)) || (pdeviceID == ((void*)0))) return 6;



    if( PAC1711_MUTEX_Lock(&(pdevice->mutexProcState)) == 0 )
    {
        return 1;
    }

    if(pdevice->processingState == Idle){

        pdevice->processingState = GetDeviceIDReq;
        pdevice->deviceEventStatus = PAC1711_EVENT_NONE;
        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
    }else{

        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
        return 1;
    }

    pdevice->outData = (void*)pdeviceID;

    pdevice->i2cTxBuffer[0] = 0xFD;
    unsigned int i2cRxSize = (1 + 1 + 1);
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) i2cRxSize += 3;
    pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
    bSuccess = PAC1711_I2C_WriteRead(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, 1,
                                               (void*) pdevice->i2cRxBuffer, i2cRxSize);
    if(bSuccess == 0){
        pdevice->processingState = Idle;
        pdevice->processError = 4;
        return 4;
    }


    retcode = RequestReturn(pdevice);
    return retcode;
}


static void PAC1711_GetDeviceIDProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    int idx = 0;

    pRawValue = pdevice->i2cRxBuffer;

    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) idx++;
    pdevice->deviceID.product = pRawValue[idx];
    ((PAC1711_deviceID_P)pdevice->outData)->product = pRawValue[idx++];


    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) idx++;
    pdevice->deviceID.manufacturer = pRawValue[idx];
    ((PAC1711_deviceID_P)pdevice->outData)->manufacturer = pRawValue[idx++];


    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) idx++;
    pdevice->deviceID.revision = pRawValue[idx];
    ((PAC1711_deviceID_P)pdevice->outData)->revision = pRawValue[idx];
}



int16_t PAC1711_RefreshReq(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_REFRESH_MODE refreshMode){
    int16_t retcode;
    _Bool bSuccess;
    if (pdevice == ((void*)0)) return 6;



    if( PAC1711_MUTEX_Lock(&(pdevice->mutexProcState)) == 0 )
    {
        return 1;
    }

    if(pdevice->processingState == Idle){

        pdevice->processingState = RefreshReq;
        pdevice->deviceEventStatus = PAC1711_EVENT_NONE;
        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
    }else
    {

        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
        return 1;
    }


    if(pdevice->negPwr_change_pending == 1){
        pdevice->negPwr_LAT_cached = 0;
        pdevice->negPwr_change_pending = 0;
    }
    if(pdevice->ctrl_change_pending == 1){
        pdevice->ctrl_LAT_cached = 0;
        pdevice->ctrl_change_pending = 0;
    }
    pdevice->accCount_cached = 0;

    switch (refreshMode){
        case PAC1711_REFRESH_G:
            pdevice->i2cTxBuffer[0] = 0x14;
            break;
        case PAC1711_REFRESH_V:
            pdevice->i2cTxBuffer[0] = 0x15;
            break;
        case PAC1711_REFRESH:
        default:
            pdevice->i2cTxBuffer[0] = 0x00;
            break;
    }

    pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
    bSuccess = PAC1711_I2C_Write(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, 1);
    if(bSuccess == 0){
        pdevice->processingState = Idle;
        pdevice->processError = 4;
        return 4;
    }


    retcode = RequestReturn(pdevice);
    return retcode;
}

int16_t PAC1711_Refresh(PAC1711_DEVICE_CONTEXT_P pdevice){
    return PAC1711_RefreshReq(pdevice, PAC1711_REFRESH);
}

int16_t PAC1711_RefreshG(PAC1711_DEVICE_CONTEXT_P pdevice){
    return PAC1711_RefreshReq(pdevice, PAC1711_REFRESH_G);
}

int16_t PAC1711_RefreshV(PAC1711_DEVICE_CONTEXT_P pdevice){
    return PAC1711_RefreshReq(pdevice, PAC1711_REFRESH_V);
}


int16_t PAC1711_GetCtrl_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t reg_select, PAC1711_CONTROL_REGFIELDS_P pCtrl_reg){
    if (pdevice == ((void*)0)) return 6;
    switch(reg_select){
        case 1:
            return PAC1711_Get_Register(pdevice, (void*)pCtrl_reg, 0x01, 2, GetCtrlRegisterReq);
        case 2:
            return PAC1711_Get_Register(pdevice, (void*)pCtrl_reg, 0x17, 2, GetCtrlRegisterReq);
        case 3:
            return PAC1711_Get_Register(pdevice, (void*)pCtrl_reg, 0x0F, 2, GetCtrlLatRegisterReq);
        default:
            return 6;
    }
}


static void PAC1711_GetCtrl_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ProcessMode procMode){
    uint8_t* pRawValue;
    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_CtrlBytesToRegfields(pRawValue, (PAC1711_CONTROL_REGFIELDS_P)pdevice->outData);


    if(procMode == ProcessCTRLlat){
        pdevice->ctrl_LAT = *((PAC1711_CONTROL_REGFIELDS_P)pdevice->outData);
        pdevice->ctrl_LAT_cached = 1;
    }
}


int16_t PAC1711_SetCtrl_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_CONTROL_REGFIELDS Ctrl_reg){
    uint8_t pregisterBytes[2];

    if (pdevice == ((void*)0)) return 6;

    PAC1711_CtrlRegfieldsToBytes(Ctrl_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x01, 2,
                                SetCtrlRegisterReq);
}


int16_t PAC1711_GetAccumulatorCount(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x02, 4, GetAccCountReq);
}


static void PAC1711_GetAccumulatorCountProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    PAC1711_Get_Reg32bitProcess(pdevice);
    pdevice->accCount = *((uint32_t*)pdevice->outData);
    pdevice->accCount_cached = 1;
}


int16_t PAC1711_SetAccumulatorCountPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val){
    uint8_t pregisterBytes[2];

    PAC1711_Reg16bitToRawBytes(register_val, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x25, 2,
                                SetRegisterReq);
}


int16_t PAC1711_GetAccumulatorCountPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x25, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetVACC_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint64_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x03, 7,
                                GetRegister56bitReq);
}


int16_t PAC1711_SetVACCPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val){
    uint8_t pregisterBytes[2];

    PAC1711_Reg16bitToRawBytes(register_val, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x26, 2,
                                SetRegisterReq);
}


int16_t PAC1711_GetVACCPreset_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x26, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetVACC(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue, uint8_t* pmode){
    if ((pdevice == ((void*)0)) || (pvalue == ((void*)0)) || (pmode == ((void*)0))) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_VACCRegister(pdevice,
                                    (void*)pvalue, pmode, 0,
                                    ProcessVACCget);
}


int16_t PAC1711_DecodeCTRLtoSampleRate(PAC1711_CONTROL_REGFIELDS ctrlReg){

    if( (ctrlReg.AA == 1) && (ctrlReg.SAMPLE_MODE < 6)){

        return 8192;
    }else{
        switch(ctrlReg.SAMPLE_MODE){
            case 0:
                return 8192;
            case 1:
                return 4096;
            case 2:
                return 1024;
            case 3:
                return 256;
            case 4:
                return 64;
            case 5:
                return 8;
            case 6:
            case 7:
            case 8:
            case 9:
            case 12:
            case 13:
                return 1;
            case 10:
            case 11:
                return 16384;
            case 14:
            case 15:
                return 0;
            default:
                return -1;
        }
    }
}


static int16_t PAC1711_GetVACCProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint64_t regVal;
    uint8_t mode;
    int16_t sampleRate;
    int16_t errorCode = 0;
    float result = 0.0;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    regVal = PAC1711_RawBytesToReg64bit(pRawBytes);

    mode = pdevice->ctrl_LAT.ACC_CONFIG;

    if(pdevice->regProcMode == ProcessVACCget){
        *((uint8_t*)pdevice->accMode) = mode;
    }

    switch(mode){
        case 0b00:
            result = PAC1711_VaccReg64bitToPower_mW(regVal, pdevice->IsSignedPower,
                                                    pdevice->VPowerScaleRange,
                                                    pdevice->is12bitADCres,
                                                    pdevice->rsense);

            switch(pdevice->regProcMode){
                case ProcessVACCget:
                    break;
                case ProcessVACCenergy:
                    sampleRate = PAC1711_DecodeCTRLtoSampleRate(pdevice->ctrl_LAT);

                    if(sampleRate <= 1) errorCode = 9;
                    result = PAC1711_VaccPowerToEnergy_mWh(result, sampleRate);
                    break;
                case ProcessVACCtimedEnergy:
                    result = PAC1711_VaccPowerTimedToEnergy_mWh(result, pdevice->accCount, pdevice->time);
                    break;
                default:
                    errorCode = 11;
                    result = 0.0;
            }
            break;

        case 0b01:
            result = PAC1711_VaccReg64bitToVoltage_mV(regVal, pdevice->IsSignedVsense,
                                                      pdevice->VsenseScaleRange,
                                                      pdevice->is12bitADCres);
            switch(pdevice->regProcMode){
                case ProcessVACCget:
                    break;
                case ProcessVACCcoulomb:
                    sampleRate = PAC1711_DecodeCTRLtoSampleRate(pdevice->ctrl_LAT);

                    if(sampleRate <= 1) errorCode = 9;
                    result = PAC1711_VaccVoltageToCoulombCnt(result, sampleRate, pdevice->rsense);
                    break;
                case ProcessVACCtimedCoulomb:
                    result = PAC1711_VaccVoltageTimedToCoulombCnt(result, pdevice->accCount, pdevice->time, pdevice->rsense);
                    break;
                default:
                    errorCode = 11;
                    result = 0.0;
            }
            break;

        case 0b10:
            if (pdevice->regProcMode == ProcessVACCget){
                result = PAC1711_VaccReg64bitToVoltage_mV(regVal, pdevice->IsSignedVbus,
                                                          pdevice->VbusScaleRange,
                                                          pdevice->is12bitADCres);

            }else{
                errorCode = 11;
                result = 0.0;
            }
            break;

        default:
            errorCode = 10;
    }
    *((float*)pdevice->outData) = result;
    return errorCode;
}



int16_t PAC1711_GetEnergy_mWh(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if ((pdevice == ((void*)0)) || (pvalue == ((void*)0))) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_VACCRegister(pdevice,
                                    (void*)pvalue, 0, 0,
                                    ProcessVACCenergy);
}



int16_t PAC1711_GetTimedEnergy_mWh(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue, uint32_t time){
    if ((pdevice == ((void*)0)) || (pvalue == ((void*)0))) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_VACCRegister(pdevice,
                                    (void*)pvalue, 0, time,
                                    ProcessVACCtimedEnergy);
}



int16_t PAC1711_GetCoulomb_mAs(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if ((pdevice == ((void*)0)) || (pvalue == ((void*)0))) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_VACCRegister(pdevice,
                                    (void*)pvalue, 0, 0,
                                    ProcessVACCcoulomb);
}



int16_t PAC1711_GetTimedCoulomb_mAs(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue, uint32_t time){
    if ((pdevice == ((void*)0)) || (pvalue == ((void*)0))) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_VACCRegister(pdevice,
                                    (void*)pvalue, 0, time,
                                    ProcessVACCtimedCoulomb);
}


int16_t PAC1711_GetVBUS_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x04, 2,
                                GetRegister16bitReq);
}

int16_t PAC1711_GetVBUS_AVG_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x06, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetVBUSmin_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x09, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetVBUSmax_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x0A, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetVBUS_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x04, 2,
                                GetVBUSvalueReq);
}


int16_t PAC1711_GetVBUS_AVG_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x06, 2,
                                GetVBUSvalueReq);
}


int16_t PAC1711_GetVBUSmin_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x09, 2,
                                GetVBUSvalueReq);
}


int16_t PAC1711_GetVBUSmax_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x0A, 2,
                                GetVBUSvalueReq);
}


static void PAC1711_GetVBUS_mVProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint16_t VbusReg;
    float VbusReal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    VbusReg = PAC1711_RawBytestoReg16bit(pRawBytes);
    VbusReal = PAC1711_VoltageReg16bitToVoltage_mV(VbusReg, pdevice->IsSignedVbus, pdevice->VbusScaleRange);
    *((float*)pdevice->outData) = VbusReal;
}

int16_t PAC1711_GetVSENSE_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x05, 2,
                                GetRegister16bitReq);
}

int16_t PAC1711_GetVSENSE_AVG_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x07, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetVSENSEmin_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x0B, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetVSENSEmax_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x0C, 2,
                                GetRegister16bitReq);
}

int16_t PAC1711_GetVSENSE_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x05, 2,
                                GetVSENSEvalueReq);
}


int16_t PAC1711_GetVSENSE_AVG_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x07, 2,
                                GetVSENSEvalueReq);
}


int16_t PAC1711_GetVSENSEmin_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x0B, 2,
                                GetVSENSEvalueReq);
}


int16_t PAC1711_GetVSENSEmax_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x0C, 2,
                                GetVSENSEvalueReq);
}


static void PAC1711_GetVSENSE_mVProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint16_t VsenseReg;
    float VsenseReal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    VsenseReg = PAC1711_RawBytestoReg16bit(pRawBytes);
    VsenseReal = PAC1711_VoltageReg16bitToVoltage_mV(VsenseReg, pdevice->IsSignedVsense, pdevice->VsenseScaleRange);
    *((float*)pdevice->outData) = VsenseReal;
}


int16_t PAC1711_GetISENSE_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if (pdevice == ((void*)0)) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x05, 2,
                                GetISENSEvalueReq);
}


int16_t PAC1711_GetISENSE_AVG_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if (pdevice == ((void*)0)) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x07, 2,
                                GetISENSEvalueReq);
}


int16_t PAC1711_GetISENSEmin_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if (pdevice == ((void*)0)) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x0B, 2,
                                GetISENSEvalueReq);
}


int16_t PAC1711_GetISENSEmax_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if (pdevice == ((void*)0)) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x0C, 2,
                                GetISENSEvalueReq);
}


static void PAC1711_GetISENSE_mAProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint16_t VsenseReg;
    float IsenseReal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    VsenseReg = PAC1711_RawBytestoReg16bit(pRawBytes);
    IsenseReal = PAC1711_VoltageReg16bitToCurrent_mA(VsenseReg, pdevice->IsSignedVsense,
                                                     pdevice->VsenseScaleRange, pdevice->rsense);
    *((float*)pdevice->outData) = IsenseReal;
}


int16_t PAC1711_GetVPOWER_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x08, 4,
                                GetRegister32bitReq);
}


int16_t PAC1711_GetVPOWERmin_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x0D, 4,
                                GetRegister32bitReq);
}


int16_t PAC1711_GetVPOWERmax_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint32_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x0E, 4,
                                GetRegister32bitReq);
}


int16_t PAC1711_GetVPOWER_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if (pdevice == ((void*)0)) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x08, 4,
                                GetVPOWERValueReq);
}


int16_t PAC1711_GetVPOWERmin_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if (pdevice == ((void*)0)) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x0D, 4,
                                GetVPOWERValueReq);
}


int16_t PAC1711_GetVPOWERmax_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    if (pdevice == ((void*)0)) return 6;

    if (pdevice->rsense == 0) return 7;
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x0E, 4,
                                GetVPOWERValueReq);
}


static void PAC1711_GetVPOWER_mWProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint32_t regVal;
    float VpowerReal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    regVal = PAC1711_RawBytestoReg32bit(pRawBytes);

    VpowerReal = PAC1711_VpowerReg32bitToPower_mW(regVal, pdevice->IsSignedPower, pdevice->VPowerScaleRange, pdevice->rsense);
    *((float*)pdevice->outData) = VpowerReal;
}


int16_t PAC1711_GetSMBusSettings_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SMBUS_SETTINGS_REGFIELDS_P pSMBus_reg){
    return PAC1711_Get_Register(pdevice, (void*)pSMBus_reg,
                                0x12, 1,
                                GetSMBusRegisterReq);
}


static void PAC1711_GetSMBusSettings_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_SMBusBytesToRegfields(pRawValue, (PAC1711_SMBUS_SETTINGS_REGFIELDS_P)pdevice->outData);


    pdevice->ENABLE_BYTE_COUNT_FLAG = ( ((PAC1711_SMBUS_SETTINGS_REGFIELDS_P)(pdevice->outData))->BYTE_COUNT == 1 ) ? 1: 0;
}


int16_t PAC1711_SetSMBusSettings_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SMBUS_SETTINGS_REGFIELDS SMBus_reg){
    uint8_t pregisterBytes[1];
    PAC1711_SMBusRegfieldsToBytes(SMBus_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x12, 1,
                                SetSMBusRegisterReq);
}


static void PAC1711_SetSMBusSettings_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice){

    pdevice->ENABLE_BYTE_COUNT_FLAG = ( ((pdevice->i2cTxBuffer[1] >> 2) & 0x01) == 1 ) ? 1: 0;
}


int16_t PAC1711_GetNegPwrFsr_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t reg_select, PAC1711_NEGPWRFSR_REGFIELDS_P pNegPwr_reg){
    if (pdevice == ((void*)0)) return 6;
    switch(reg_select){
        case 1:
            return PAC1711_Get_Register(pdevice, (void*)pNegPwr_reg, 0x13, 1, GetNegPWRFSRRegisterReq);
        case 2:
            return PAC1711_Get_Register(pdevice, (void*)pNegPwr_reg, 0x18, 1, GetNegPWRFSRRegisterReq);
        case 3:
            return PAC1711_Get_Register(pdevice, (void*)pNegPwr_reg, 0x10, 1, GetNegPWRFSRLatRegisterReq);
        default:
            return 6;
    }
}


static void PAC1711_GetNegPwrFsr_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ProcessMode procMode){
uint8_t* pRawValue;
    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_NegPwrFsrBytesToRegfields(pRawValue, (PAC1711_NEGPWRFSR_REGFIELDS_P)pdevice->outData);
    if(procMode == ProcessNEGPWRlat){
        pdevice->negPwrFsr_LAT = *((PAC1711_NEGPWRFSR_REGFIELDS_P)pdevice->outData);
        pdevice->negPwr_LAT_cached = 1;
        PAC1711_UpdateContext_ScaleValues(pdevice);
    }
}


int16_t PAC1711_SetNegPwrFsr_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_NEGPWRFSR_REGFIELDS NegPwr_reg){
    uint8_t pregisterBytes[1];
    if (pdevice == ((void*)0)) return 6;
    PAC1711_NegPwrFsrRegfieldsToBytes(NegPwr_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x13, 1,
                                SetNegPWRFSRRegisterReq);
}


int16_t PAC1711_GetSlow_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SLOW_REGFIELDS_P pSlow_reg){
    return PAC1711_Get_Register(pdevice, (void*)pSlow_reg,
                                0x16, 1,
                                GetSlowRegisterReq);
}


static void PAC1711_GetSlow_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_SlowBytesToRegfields(pRawValue, (PAC1711_SLOW_REGFIELDS_P)pdevice->outData);
}


int16_t PAC1711_SetSlow_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_SLOW_REGFIELDS Slow_reg){
    uint8_t pregisterBytes[1];
    PAC1711_SlowRegfieldsToBytes(Slow_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x16, 1,
                                SetRegisterReq);
}


int16_t PAC1711_GetAlertStatus_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_STATUS_REGFIELDS_P pAlertStatus_reg){
    return PAC1711_Get_Register(pdevice, (void*)pAlertStatus_reg,
                                0x11, 2,
                                GetAlertStatusRegisterReq);
}


static void PAC1711_GetAlertStatus_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;

    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_AlertStatusBytesToRegfields(pRawValue, (PAC1711_ALERT_STATUS_REGFIELDS_P)pdevice->outData);
}


int16_t PAC1711_GetAlertEnable_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS_P pAlertEnable_reg){
    return PAC1711_Get_Register(pdevice, (void*)pAlertEnable_reg,
                                0x24, 2,
                                GetAlertConfigRegisterReq);
}


int16_t PAC1711_GetSlowAlert0_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS_P pSlowAlert0_reg){
    return PAC1711_Get_Register(pdevice, (void*)pSlowAlert0_reg,
                                0x19, 2,
                                GetAlertConfigRegisterReq);
}


int16_t PAC1711_GetGpioAlert1_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS_P pGpioAlert1_reg){
    return PAC1711_Get_Register(pdevice, (void*)pGpioAlert1_reg,
                                0x1A, 2,
                                GetAlertConfigRegisterReq);
}


static void PAC1711_GetAlert_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;

    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_AlertEnableBytesToRegfields(pRawValue, (PAC1711_ALERT_ENABLE_REGFIELDS_P)pdevice->outData);
}


int16_t PAC1711_SetAlertEnable_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS AlertEnable_reg){
    uint8_t pregisterBytes[2];

    PAC1711_AlertEnableRegfieldsToBytes(AlertEnable_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x24, 2,
                                SetRegisterReq);
}


int16_t PAC1711_SetSlowAlert0_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS AlertEnable_reg){
    uint8_t pregisterBytes[2];

    PAC1711_AlertEnableRegfieldsToBytes(AlertEnable_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x19, 2,
                                SetRegisterReq);
}


int16_t PAC1711_SetGpioAlert1_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ALERT_ENABLE_REGFIELDS AlertEnable_reg){
    uint8_t pregisterBytes[2];

    PAC1711_AlertEnableRegfieldsToBytes(AlertEnable_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x1A, 2,
                                SetRegisterReq);
}


int16_t PAC1711_GetAccFullness_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ACCUM_LIMITS_REGFIELDS_P pAccFullnessLimits_reg){
    return PAC1711_Get_Register(pdevice, (void*)pAccFullnessLimits_reg,
                                0x1B, 1,
                                GetAccFullnessRegisterReq);
}


static void PAC1711_GetAccFullness_regProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_AccFullnessBytesToRegfields(pRawValue, (PAC1711_ACCUM_LIMITS_REGFIELDS_P)pdevice->outData);
}


int16_t PAC1711_SetAccFullness_reg(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_ACCUM_LIMITS_REGFIELDS AccFullnessLimits_reg){
    uint8_t pregisterBytes[1];
    PAC1711_AccFullnessRegfieldsToBytes(AccFullnessLimits_reg, pregisterBytes);

    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x1B, 1,
                                SetRegisterReq);
}


int16_t PAC1711_GetOClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x1C, 1,
                                GetRegister8bitReq);
}


int16_t PAC1711_GetOClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x1C, 1,
                                GetCurrentLimitValueReq);
}


static void PAC1711_GetCurrentLimit_mAProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    float limitReal;

    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    limitReal = PAC1711_CLimitRegisterToCurrent_mA(pRawValue[0], pdevice->VsenseMAX, pdevice->rsense);
    *((float*)pdevice->outData) = limitReal;
}


int16_t PAC1711_SetOClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val){
    return PAC1711_Set_Register(pdevice, &register_val,
                                0x1C, 1,
                                SetRegisterReq);
}


int16_t PAC1711_SetOClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float value){
    uint8_t limitRegister;

    if (pdevice == ((void*)0)) return 6;

    limitRegister = PAC1711_Climit_mAtoRegisterVal(value, pdevice->VsenseMAX, pdevice->rsense);
    if(limitRegister == 0x7F){
        limitRegister = 0x7F - 1;
    }
    return PAC1711_Set_Register(pdevice, &limitRegister,
                                0x1C, 1,
                                SetRegisterReq);
}


int16_t PAC1711_GetUClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x1D, 1,
                                GetRegister8bitReq);
}


int16_t PAC1711_GetUClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x1D, 1,
                                GetCurrentLimitValueReq);
}


int16_t PAC1711_SetUClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val){
    return PAC1711_Set_Register(pdevice, &register_val,
                                0x1D, 1,
                                SetRegisterReq);
}


int16_t PAC1711_SetUClimit_mA(PAC1711_DEVICE_CONTEXT_P pdevice, float value){
    uint8_t limitRegister;

    if (pdevice == ((void*)0)) return 6;

    limitRegister = PAC1711_Climit_mAtoRegisterVal(value, pdevice->VsenseMAX, pdevice->rsense);
    if(limitRegister == 0x80){
        limitRegister = 0x80 + 1;
    }
    return PAC1711_Set_Register(pdevice, &limitRegister,
                                0x1D, 1,
                                SetRegisterReq);

}


int16_t PAC1711_GetOPWlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x1E, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetOPWlimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x1E, 2,
                                GetPowerLimitValueReq);
}


int16_t PAC1711_SetOPWlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val){
    uint8_t pregisterBytes[2];

    PAC1711_Reg16bitToRawBytes(register_val, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x1E, 2,
                                SetRegisterReq);
}


int16_t PAC1711_SetOPWlimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float value){
    uint16_t limitRegister;
    uint8_t pregisterBytes[2];

    if (pdevice == ((void*)0)) return 6;

    limitRegister = PAC1711_Plimit_mWtoRegisterVal(value, pdevice->VPowerMAX, pdevice->rsense);
    if(limitRegister == 0x7FFF){
        limitRegister = 0x7FFF - 1;
    }
    PAC1711_Reg16bitToRawBytes(limitRegister, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x1E, 2,
                                SetRegisterReq);
}


int16_t PAC1711_GetOPClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x1F, 2,
                                GetRegister16bitReq);
}


int16_t PAC1711_GetOPClimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x1F, 2,
                                GetPowerLimitValueReq);
}


static void PAC1711_GetPowerLimit_mWProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint16_t limitRegister;
    float limitReal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    limitRegister = PAC1711_RawBytestoReg16bit(pRawBytes);
    limitReal = PAC1711_PLimitRegisterToPower_mW(limitRegister, pdevice->VPowerMAX, pdevice->rsense);
    *((float*)pdevice->outData) = limitReal;
}


int16_t PAC1711_SetOPClimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint16_t register_val){
    uint8_t pregisterBytes[2];

    PAC1711_Reg16bitToRawBytes(register_val, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x1F, 2,
                                SetRegisterReq);
}


int16_t PAC1711_SetOPClimit_mW(PAC1711_DEVICE_CONTEXT_P pdevice, float value){
    uint16_t limitRegister;
    uint8_t pregisterBytes[2];

    if (pdevice == ((void*)0)) return 6;

    limitRegister = PAC1711_Plimit_mWtoRegisterVal(value, pdevice->VPowerMAX, pdevice->rsense);
    if(limitRegister == 0x7FFF){
        limitRegister = 0x7FFF - 1;
    }
    PAC1711_Reg16bitToRawBytes(limitRegister, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x1F, 2,
                                SetRegisterReq);
}


int16_t PAC1711_GetOVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x20, 1,
                                GetRegister8bitReq);
}


int16_t PAC1711_GetOVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x20, 1,
                                GetVoltageLimitValueReq);
}


static void PAC1711_GetVoltageLimit_mVProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    float limitReal;

    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    limitReal = PAC1711_VLimitRegisterToVoltage_mV(pRawValue[0], pdevice->VbusMAX);
    *((float*)pdevice->outData) = limitReal;
}


int16_t PAC1711_SetOVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val){
    return PAC1711_Set_Register(pdevice, &register_val,
                                0x20, 1,
                                SetRegisterReq);
}


int16_t PAC1711_SetOVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float value){
    uint8_t limitRegister;

    if (pdevice == ((void*)0)) return 6;

    limitRegister = PAC1711_Vlimit_mVtoRegisterVal(value, pdevice->VbusMAX);
    if(limitRegister == 0x7F){
        limitRegister = 0x7F - 1;
    }
    return PAC1711_Set_Register(pdevice, &limitRegister,
                                0x20, 1,
                                SetRegisterReq);
}


int16_t PAC1711_GetUVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t* pregister_val){
    return PAC1711_Get_Register(pdevice, (void*)pregister_val,
                                0x21, 1,
                                GetRegister8bitReq);
}



int16_t PAC1711_GetUVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float* pvalue){
    return PAC1711_Get_Register(pdevice, (void*)pvalue,
                                0x21, 1,
                                GetVoltageLimitValueReq);
}


int16_t PAC1711_SetUVlimit_reg(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t register_val){
    return PAC1711_Set_Register(pdevice, &register_val,
                                0x21, 1,
                                SetRegisterReq);
}


int16_t PAC1711_SetUVlimit_mV(PAC1711_DEVICE_CONTEXT_P pdevice, float value){
    uint8_t limitRegister;

    if (pdevice == ((void*)0)) return 6;

    limitRegister = PAC1711_Vlimit_mVtoRegisterVal(value, pdevice->VbusMAX);
    if(limitRegister == 0x80){
        limitRegister = 0x80 + 1;
    }
    return PAC1711_Set_Register(pdevice, &limitRegister,
                                0x21, 1,
                                SetRegisterReq);
}


int16_t PAC1711_GetStepLimit(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_STEP_LIMIT_REGFIELDS_P pStepLimit_reg){
    return PAC1711_Get_Register(pdevice, (void*)pStepLimit_reg,
                                0x22, 1,
                                GetStepLimitRegisterReq);
}


static void PAC1711_GetStepLimitProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;

    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_StepLimitBytesToRegfields(pRawValue, (PAC1711_STEP_LIMIT_REGFIELDS_P)pdevice->outData);
}


int16_t PAC1711_SetStepLimit(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_STEP_LIMIT_REGFIELDS StepLimit_reg){
    uint8_t pregisterBytes[1];
    PAC1711_StepLimitRegfieldsToBytes(StepLimit_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x22, 1,
                                SetRegisterReq);
}


int16_t PAC1711_GetLimitNsamples(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_LIMIT_NSAMPLES_REGFIELDS_P pLimitNsamples_reg){
    return PAC1711_Get_Register(pdevice, (void*)pLimitNsamples_reg,
                                0x23, 2,
                                GetLimitNsamplesRegisterReq);
}


static void PAC1711_GetLimitNsamplesProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;

    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_NsamplesBytesToRegfields(pRawValue, (PAC1711_LIMIT_NSAMPLES_REGFIELDS_P)pdevice->outData);
}


int16_t PAC1711_SetLimitNsamples(PAC1711_DEVICE_CONTEXT_P pdevice, PAC1711_LIMIT_NSAMPLES_REGFIELDS LimitNsamples_reg){
    uint8_t pregisterBytes[2];
    PAC1711_NsamplesRegfieldsToBytes(LimitNsamples_reg, pregisterBytes);
    return PAC1711_Set_Register(pdevice, pregisterBytes,
                                0x23, 2,
                                SetRegisterReq);
}


static int16_t PAC1711_UpdateContext_ChannelPolarity(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t registerAddr;
    int16_t errorCode = 0;
    _Bool bSuccess;


    if(pdevice->negPwr_LAT_cached == 0){
        registerAddr = 0x10;
        pdevice->i2cTxBuffer[0] = registerAddr;

        unsigned int i2cRxSize = 1;
        if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) i2cRxSize++;
        pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
        bSuccess = PAC1711_I2C_WriteRead(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, 1,
                                                   (void*) pdevice->i2cRxBuffer_negPwr, i2cRxSize);
        if(bSuccess == 0){
            return 4;
        }
    }
    else
    {
        errorCode = 1000;
    }

   return errorCode;
}


static void PAC1711_UpdateContext_ChannelPolarityProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    pRawValue = pdevice->i2cRxBuffer_negPwr;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_NegPwrFsrBytesToRegfields(pRawValue, &(pdevice->negPwrFsr_LAT));
    pdevice->negPwr_LAT_cached = 1;
    PAC1711_UpdateContext_ScaleValues(pdevice);
}


static int16_t PAC1711_UpdateContext_Ctrl(PAC1711_DEVICE_CONTEXT_P pdevice){
    int16_t errorCode = 0;
    uint8_t registerAddr;
    _Bool bSuccess;



    if(pdevice->ctrl_LAT_cached == 0){
        registerAddr = 0x0F;
        pdevice->i2cTxBuffer[0] = registerAddr;

        unsigned int i2cRxSize = 2;
        if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) i2cRxSize++;
        pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
        bSuccess = PAC1711_I2C_WriteRead(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, 1,
                                                    (void*) pdevice->i2cRxBuffer_ctrl, i2cRxSize);
        if(bSuccess == 0){
            return 4;
        }
    }
    else
    {
        errorCode = 1000;
    }

    return errorCode;
}

static void PAC1711_UpdateContext_CtrlProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;
    pRawValue = pdevice->i2cRxBuffer_ctrl;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;
    PAC1711_CtrlBytesToRegfields(pRawValue, &(pdevice->ctrl_LAT));
    pdevice->ctrl_LAT_cached = 1;
}


static int16_t PAC1711_UpdateContext_AccumulatorCount(PAC1711_DEVICE_CONTEXT_P pdevice){
    int16_t errorCode = 0;
    _Bool bSuccess;


    if(pdevice->accCount_cached == 0){
        pdevice->i2cTxBuffer[0] = 0x02;
        unsigned int i2cRxSize = 4;
        if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) i2cRxSize++;
        pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
        bSuccess = PAC1711_I2C_WriteRead(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, 1,
                                                    (void*) pdevice->i2cRxBuffer_accCount, i2cRxSize);
        if(bSuccess == 0){
            return 4;
        }
    }
    else
    {
        errorCode = 1000;
    }
    return errorCode;
}


static void PAC1711_UpdateContext_AccumulatorCountProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    pRawBytes = pdevice->i2cRxBuffer_accCount;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    pdevice->accCount = PAC1711_RawBytestoReg32bit(pRawBytes);
    pdevice->accCount_cached = 1;
}


static int16_t PAC1711_Get_Register(PAC1711_DEVICE_CONTEXT_P pdevice,
                                    void* pregister_val, uint8_t registerAddr, size_t regSize,
                                    PAC1711_procState processingState){
    int16_t retcode;
    _Bool bSuccess;

    if ((pdevice == ((void*)0)) || (pregister_val == ((void*)0))) return 6;



    if( PAC1711_MUTEX_Lock(&(pdevice->mutexProcState)) == 0 )
    {
        return 1;
    }

    if(pdevice->processingState == Idle){

        pdevice->processingState = processingState;
        pdevice->deviceEventStatus = PAC1711_EVENT_NONE;
        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
    }else
    {

        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
        return 1;
    }

    pdevice->outData = (void*)pregister_val;
    pdevice->i2cTxBuffer[0] = registerAddr;

    size_t i2cRxSize = regSize;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) i2cRxSize++;

    pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
    bSuccess = PAC1711_I2C_WriteRead(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, 1,
                                                (void*) pdevice->i2cRxBuffer, i2cRxSize);
    if(bSuccess == 0){
        pdevice->processingState = Idle;
        pdevice->processError = 4;
        return 4;
    }


    retcode = RequestReturn(pdevice);
    return retcode;
}


static int16_t PAC1711_Get_VACCRegister(PAC1711_DEVICE_CONTEXT_P pdevice,
                                        void* pregister_val, uint8_t* pmode, uint32_t time,
                                        PAC1711_ProcessMode procMode){
    int16_t retcode;
    _Bool bSuccess;






    if( PAC1711_MUTEX_Lock(&(pdevice->mutexProcState)) == 0 )
    {
        return 1;
    }

    if(pdevice->processingState == Idle){

        pdevice->processingState = GetVACCValueReq;
        pdevice->deviceEventStatus = PAC1711_EVENT_NONE;
        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
    }else
    {

        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
        return 1;
    }


    pdevice->regProcMode = procMode;
    pdevice->accMode = pmode;
    pdevice->time = time;

    pdevice->outData = (void*)pregister_val;
    pdevice->i2cTxBuffer[0] = 0x03;

    size_t i2cRxSize = 7;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) i2cRxSize++;

    pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
    bSuccess = PAC1711_I2C_WriteRead(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, 1,
                                                (void*) pdevice->i2cRxBuffer, i2cRxSize);
    if(bSuccess == 0){
        pdevice->processingState = Idle;
        pdevice->processError = 4;
        return 4;
    }


    retcode = RequestReturn(pdevice);
    return retcode;
}


static void PAC1711_Get_Reg8bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawValue;

    pRawValue = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawValue++;

    *((uint8_t*)pdevice->outData) = (uint8_t)pRawValue[0];
}


static void PAC1711_Get_Reg16bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint16_t regVal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    regVal = PAC1711_RawBytestoReg16bit(pRawBytes);
    *((uint16_t*)pdevice->outData) = regVal;
}


static void PAC1711_Get_Reg32bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint32_t regVal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    regVal = PAC1711_RawBytestoReg32bit(pRawBytes);
    *((uint32_t*)pdevice->outData) = regVal;
}


static void PAC1711_Get_Reg56bitProcess(PAC1711_DEVICE_CONTEXT_P pdevice){
    uint8_t* pRawBytes;
    uint64_t regVal;

    pRawBytes = pdevice->i2cRxBuffer;
    if(pdevice->ENABLE_BYTE_COUNT_FLAG == 1) pRawBytes++;
    regVal = PAC1711_RawBytesToReg64bit(pRawBytes);
    *((uint64_t*)pdevice->outData) = regVal;
}


static int16_t PAC1711_Set_Register(PAC1711_DEVICE_CONTEXT_P pdevice, uint8_t *pregisterBytes, uint8_t registerAddr, size_t regSize, PAC1711_procState processingState){
    int16_t retcode;
    _Bool bSuccess;

    if (pdevice == ((void*)0)) return 6;




    if( PAC1711_MUTEX_Lock(&(pdevice->mutexProcState)) == 0 )
    {
        return 1;
    }

    if(pdevice->processingState == Idle){

        pdevice->processingState = processingState;
        pdevice->deviceEventStatus = PAC1711_EVENT_NONE;
        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
    }else
    {

        PAC1711_MUTEX_Unlock(&(pdevice->mutexProcState));
        return 1;
    }

    pdevice->i2cTxBuffer[0] = registerAddr;
    for(int cnt=0; cnt < regSize; cnt++){
        pdevice->i2cTxBuffer[cnt+1] = pregisterBytes[cnt];
    }

    pdevice->i2cCommStatus = PAC1711_I2C_TRANSFER_NO_EVENT;
    bSuccess = PAC1711_I2C_Write(&(pdevice->i2c_context), (void*) pdevice->i2cTxBuffer, (regSize + 1));
    if(bSuccess == 0){
        pdevice->processingState = Idle;
        pdevice->processError = 4;
        return 4;
    }

    retcode = RequestReturn(pdevice);
    return retcode;
}


static __attribute__((inline)) void PAC1711_UpdateContext_ScaleValues(PAC1711_DEVICE_CONTEXT_P pdevice){
    (pdevice->VbusScaleRange) = PAC1711_VbusScaleRange(pdevice->VbusMAX, pdevice->negPwrFsr_LAT);
    (pdevice->VsenseScaleRange) = PAC1711_VsenseScaleRange(pdevice->VsenseMAX, pdevice->negPwrFsr_LAT);
    (pdevice->VPowerScaleRange) = PAC1711_VpowerScaleRange(pdevice->VPowerMAX, pdevice->negPwrFsr_LAT);

    pdevice->IsSignedPower = PAC1711_IsSignedVpower(pdevice->negPwrFsr_LAT);
    pdevice->IsSignedVsense = PAC1711_IsSignedVsense(pdevice->negPwrFsr_LAT);
    pdevice->IsSignedVbus = PAC1711_IsSignedVbus(pdevice->negPwrFsr_LAT);
}


void PAC1711_CtrlBytesToRegfields(uint8_t* pCtrlBytes, PAC1711_CONTROL_REGFIELDS_P pCtrlRegfields){

    pCtrlRegfields->SAMPLE_MODE = (pCtrlBytes[0] >> 4) & 0x0F;
    pCtrlRegfields->GPIO_ALERT1 = (pCtrlBytes[0] >> 2) & 0x03;
    pCtrlRegfields->SLOW_ALERT0 = (pCtrlBytes[0] ) & 0x03;
    pCtrlRegfields->AVERAGE = (pCtrlBytes[1] >> 5) & 0x07;
    pCtrlRegfields->AA = (pCtrlBytes[1] >> 4) & 0x01;
    pCtrlRegfields->ACC_CONFIG = (pCtrlBytes[1] >> 2) & 0x03;
    pCtrlRegfields->AUTO_REFRESH = (pCtrlBytes[1] ) & 0x03;
}


void PAC1711_CtrlRegfieldsToBytes(PAC1711_CONTROL_REGFIELDS CtrlRegfields, uint8_t* pCtrlBytes){

    pCtrlBytes[0] = (uint8_t)(
                    (CtrlRegfields.SAMPLE_MODE << 4) |
                    (CtrlRegfields.GPIO_ALERT1 << 2) |
                    (CtrlRegfields.SLOW_ALERT0 ));

    pCtrlBytes[1] = (uint8_t)(
                    (CtrlRegfields.AVERAGE << 5) |
                    (CtrlRegfields.AA << 4) |
                    (CtrlRegfields.ACC_CONFIG << 2) |
                    (CtrlRegfields.AUTO_REFRESH ));
}


void PAC1711_SMBusBytesToRegfields(uint8_t* pSMBusBytes, PAC1711_SMBUS_SETTINGS_REGFIELDS_P pSMBusRegfields){

    pSMBusRegfields->GPIO_DATA1 = (pSMBusBytes[0] >> 7) & 0x01;
    pSMBusRegfields->GPIO_DATA0 = (pSMBusBytes[0] >> 6) & 0x01;
    pSMBusRegfields->ANY_ALERT = (pSMBusBytes[0] >> 5) & 0x01;
    pSMBusRegfields->POR = (pSMBusBytes[0] >> 4) & 0x01;
    pSMBusRegfields->TIMEOUT = (pSMBusBytes[0] >> 3) & 0x01;
    pSMBusRegfields->BYTE_COUNT = (pSMBusBytes[0] >> 2) & 0x01;
    pSMBusRegfields->I2C_HISPEED = (pSMBusBytes[0] ) & 0x01;
}


void PAC1711_SMBusRegfieldsToBytes(PAC1711_SMBUS_SETTINGS_REGFIELDS SMBusRegfields, uint8_t* pSMBusBytes){
    pSMBusBytes[0] = (uint8_t)(
                     (SMBusRegfields.GPIO_DATA1 << 7) |
                     (SMBusRegfields.GPIO_DATA0 << 6) |
                     (SMBusRegfields.ANY_ALERT << 5) |
                     (SMBusRegfields.POR << 4) |
                     (SMBusRegfields.TIMEOUT << 3) |
                     (SMBusRegfields.BYTE_COUNT << 2) |
                     (SMBusRegfields.I2C_HISPEED ));
}


void PAC1711_NegPwrFsrBytesToRegfields(uint8_t* pNegPwrFsrBytes, PAC1711_NEGPWRFSR_REGFIELDS_P pNegPwrFsrRegfields){
    pNegPwrFsrRegfields->CFG_VS = (pNegPwrFsrBytes[0] >> 2) & 0x03;
    pNegPwrFsrRegfields->CFG_VB = (pNegPwrFsrBytes[0] ) & 0x03;
}


void PAC1711_NegPwrFsrRegfieldsToBytes(PAC1711_NEGPWRFSR_REGFIELDS NegPwrFsrRegfields, uint8_t* pNegPwrFsrBytes){
    pNegPwrFsrBytes[0] = (uint8_t)((NegPwrFsrRegfields.CFG_VS << 2) |
                                   (NegPwrFsrRegfields.CFG_VB ));
}


void PAC1711_SlowBytesToRegfields(uint8_t* pSlowBytes, PAC1711_SLOW_REGFIELDS_P pSlowRegfields){
    pSlowRegfields->Slow = (pSlowBytes[0] >> 7) & 0x01;
    pSlowRegfields->SlowLowHigh = (pSlowBytes[0] >> 6) & 0x01;
    pSlowRegfields->SlowHighLow = (pSlowBytes[0] >> 5) & 0x01;
    pSlowRegfields->RefreshRise = (pSlowBytes[0] >> 4) & 0x01;
    pSlowRegfields->RefreshVRise = (pSlowBytes[0] >> 3) & 0x01;
    pSlowRegfields->RefreshFall = (pSlowBytes[0] >> 2) & 0x01;
    pSlowRegfields->RefreshVFall = (pSlowBytes[0] >> 1) & 0x01;
}


void PAC1711_SlowRegfieldsToBytes(PAC1711_SLOW_REGFIELDS SlowRegfields, uint8_t* pSlowBytes){
    pSlowBytes[0] = (uint8_t)(
                    (SlowRegfields.Slow << 7) |
                    (SlowRegfields.SlowLowHigh << 6) |
                    (SlowRegfields.SlowHighLow << 5) |
                    (SlowRegfields.RefreshRise << 4) |
                    (SlowRegfields.RefreshVRise << 3) |
                    (SlowRegfields.RefreshFall << 2) |
                    (SlowRegfields.RefreshVFall << 1));
}


void PAC1711_AlertStatusBytesToRegfields(uint8_t* pAlertBytes, PAC1711_ALERT_STATUS_REGFIELDS_P pAlertStatusRegfields){
    pAlertStatusRegfields->RV = (pAlertBytes[0] >> 5) & 0x01;
    pAlertStatusRegfields->FV = (pAlertBytes[0] >> 4) & 0x01;
    pAlertStatusRegfields->RC = (pAlertBytes[0] >> 3) & 0x01;
    pAlertStatusRegfields->FC = (pAlertBytes[0] >> 2) & 0x01;
    pAlertStatusRegfields->OC = (pAlertBytes[0] >> 1) & 0x01;
    pAlertStatusRegfields->UC = pAlertBytes[0] & 0x01;

    pAlertStatusRegfields->OV = (pAlertBytes[1] >> 7) & 0x01;
    pAlertStatusRegfields->UV = (pAlertBytes[1] >> 6) & 0x01;
    pAlertStatusRegfields->OPC = (pAlertBytes[1] >> 5) & 0x01;
    pAlertStatusRegfields->OPW = (pAlertBytes[1] >> 4) & 0x01;
    pAlertStatusRegfields->ACC_OVF = (pAlertBytes[1] >> 3) & 0x01;
    pAlertStatusRegfields->ACC_COUNT = (pAlertBytes[1] >> 2) & 0x01;

}


void PAC1711_AlertEnableBytesToRegfields(uint8_t* pAlertBytes, PAC1711_ALERT_ENABLE_REGFIELDS_P pAlertEnableRegfields){
    pAlertEnableRegfields->RV = (pAlertBytes[0] >> 5) & 0x01;
    pAlertEnableRegfields->FV = (pAlertBytes[0] >> 4) & 0x01;
    pAlertEnableRegfields->RC = (pAlertBytes[0] >> 3) & 0x01;
    pAlertEnableRegfields->FC = (pAlertBytes[0] >> 2) & 0x01;
    pAlertEnableRegfields->OC = (pAlertBytes[0] >> 1) & 0x01;
    pAlertEnableRegfields->UC = pAlertBytes[0] & 0x01;

    pAlertEnableRegfields->OV = (pAlertBytes[1] >> 7) & 0x01;
    pAlertEnableRegfields->UV = (pAlertBytes[1] >> 6) & 0x01;
    pAlertEnableRegfields->OPC = (pAlertBytes[1] >> 5) & 0x01;
    pAlertEnableRegfields->OPW = (pAlertBytes[1] >> 4) & 0x01;
    pAlertEnableRegfields->ACC_OVF = (pAlertBytes[1] >> 3) & 0x01;
    pAlertEnableRegfields->ACC_COUNT = (pAlertBytes[1] >> 2) & 0x01;
    pAlertEnableRegfields->ALERT_CCx = (pAlertBytes[1] >> 1) & 0x01;
}


void PAC1711_AlertEnableRegfieldsToBytes(PAC1711_ALERT_ENABLE_REGFIELDS AlertEnableRegfields, uint8_t* pAlertBytes){

    pAlertBytes[0] = (uint8_t)(
                     (AlertEnableRegfields.RV << 5) |
                     (AlertEnableRegfields.FV << 4) |
                     (AlertEnableRegfields.RC << 3) |
                     (AlertEnableRegfields.FC << 2) |
                     (AlertEnableRegfields.OC << 1) |
                     (AlertEnableRegfields.UC ));

    pAlertBytes[1] = (uint8_t)(
                     (AlertEnableRegfields.OV << 7) |
                     (AlertEnableRegfields.UV << 6) |
                     (AlertEnableRegfields.OPC << 5) |
                     (AlertEnableRegfields.OPW << 4) |
                     (AlertEnableRegfields.ACC_OVF << 3) |
                     (AlertEnableRegfields.ACC_COUNT << 2) |
                     (AlertEnableRegfields.ALERT_CCx << 1));
}


void PAC1711_AccFullnessBytesToRegfields(uint8_t* pAccFullnessBytes, PAC1711_ACCUM_LIMITS_REGFIELDS_P pAccFullnessRegfields){
    pAccFullnessRegfields->ACC_FULL = (pAccFullnessBytes[0] >> 2) & 0x3F;
    pAccFullnessRegfields->ACC_COUNT_FULL = (pAccFullnessBytes[0] ) & 0x03;
}


void PAC1711_AccFullnessRegfieldsToBytes(PAC1711_ACCUM_LIMITS_REGFIELDS AccFullnessRegfields, uint8_t* pAccFullnessBytes){
    pAccFullnessBytes[0] = (uint8_t)((AccFullnessRegfields.ACC_FULL << 2) |
                                     (AccFullnessRegfields.ACC_COUNT_FULL ));
}


void PAC1711_StepLimitBytesToRegfields(uint8_t* pStepLimitBytes, PAC1711_STEP_LIMIT_REGFIELDS_P pStepLimitRegfields){
    pStepLimitRegfields->STEP_RV = (pStepLimitBytes[0] >> 6) & 0x03;
    pStepLimitRegfields->STEP_FV = (pStepLimitBytes[0] >> 4) & 0x03;
    pStepLimitRegfields->STEP_RC = (pStepLimitBytes[0] >> 2) & 0x03;
    pStepLimitRegfields->STEP_FC = (pStepLimitBytes[0] ) & 0x03;
}


void PAC1711_StepLimitRegfieldsToBytes(PAC1711_STEP_LIMIT_REGFIELDS StepLimitRegfields, uint8_t* pStepLimitBytes){
    pStepLimitBytes[0] = (uint8_t)(
                          (StepLimitRegfields.STEP_RV << 6) |
                          (StepLimitRegfields.STEP_FV << 4) |
                          (StepLimitRegfields.STEP_RC << 2) |
                          (StepLimitRegfields.STEP_FC ));
}


void PAC1711_NsamplesBytesToRegfields(uint8_t* pNsamplesBytes, PAC1711_LIMIT_NSAMPLES_REGFIELDS_P pNsamplesRegfields){
    pNsamplesRegfields->Nsamples_OPC = (pNsamplesBytes[0] >> 2) & 0x03;
    pNsamplesRegfields->Nsamples_OPW = (pNsamplesBytes[0] ) & 0x03;
    pNsamplesRegfields->Nsamples_OC = (pNsamplesBytes[1] >> 6) & 0x03;
    pNsamplesRegfields->Nsamples_UC = (pNsamplesBytes[1] >> 4) & 0x03;
    pNsamplesRegfields->Nsamples_OV = (pNsamplesBytes[1] >> 2) & 0x03;
    pNsamplesRegfields->Nsamples_UV = (pNsamplesBytes[1] ) & 0x03;
}


void PAC1711_NsamplesRegfieldsToBytes(PAC1711_LIMIT_NSAMPLES_REGFIELDS NsamplesRegfields, uint8_t* pNsamplesBytes){

    pNsamplesBytes[0] = (uint8_t)(
                          (NsamplesRegfields.Nsamples_OPC << 2) |
                          (NsamplesRegfields.Nsamples_OPW ));
    pNsamplesBytes[1] = (uint8_t)(
                          (NsamplesRegfields.Nsamples_OC << 6) |
                          (NsamplesRegfields.Nsamples_UC << 4) |
                          (NsamplesRegfields.Nsamples_OV << 2) |
                          (NsamplesRegfields.Nsamples_UV ));
}


float PAC1711_VaccReg64bitToPower_mW(uint64_t VAccReg, _Bool IsSignedPower, uint16_t VPowerScaleRange, _Bool is12bitADCres, uint32_t rsense){
    float VpowerAccReal, PowerUnit;

    if(rsense == 0) return 0.0;

    if(IsSignedPower == 1){
        if( (VAccReg & 0x80000000000000) == 0x80000000000000){
            VAccReg = VAccReg | 0xFF80000000000000;
        }
        VpowerAccReal = (float)((int64_t)VAccReg);
    }else{
        VpowerAccReal = (float)(VAccReg);
    }

    PowerUnit = (float)VPowerScaleRange / (float)rsense;
    if(is12bitADCres == 1){
        PowerUnit = PowerUnit * (1000000.0 / 16777216.0);
    }else{
        PowerUnit = PowerUnit * (1000000.0 / 4294967296.0);
    }
    VpowerAccReal = VpowerAccReal * PowerUnit;
    return VpowerAccReal;
}


float PAC1711_VaccReg64bitToVoltage_mV(uint64_t VAccReg, _Bool IsSignedVoltage, uint16_t VoltageScaleRange, _Bool is12bitADCres){
    float VAccReal, VoltageLsb;

    if(IsSignedVoltage == 1){
        if( (VAccReg & 0x80000000000000) == 0x80000000000000){
            VAccReg = VAccReg | 0xFF80000000000000;
        }
        VAccReal = (float)((int64_t)VAccReg);
    }else{
        VAccReal = (float)(VAccReg);
    }

    if(is12bitADCres == 1){
        VoltageLsb = VoltageScaleRange / 4096.0;
    }else{
        VoltageLsb = VoltageScaleRange / 65536.0;
    }
    VAccReal = VAccReal * VoltageLsb;
    return VAccReal;
}


float PAC1711_VoltageReg16bitToVoltage_mV(uint16_t VoltageReg, _Bool IsSignedVoltage, uint16_t VoltageScaleRange){
    float VoltReal;
    if (IsSignedVoltage == 1){
        int16_t signedReg;
        int32_t tempProd;
        signedReg = (int16_t)VoltageReg;
        tempProd = (int32_t)signedReg * (int32_t)VoltageScaleRange;
        VoltReal = (float)tempProd;
    }else{
        uint32_t tempProd;
        tempProd = (uint32_t)VoltageReg * (uint32_t)VoltageScaleRange;
        VoltReal = (float)tempProd;
    }

    VoltReal = VoltReal / 65536.0;
    return VoltReal;
}


float PAC1711_VoltageReg16bitToCurrent_mA(uint16_t VsenseReg, _Bool IsSignedVoltage, uint16_t VsenseScaleRange, uint32_t rsense){
    float VsenseReal, IsenseReal;

    if(rsense == 0) return 0.0;

    VsenseReal = PAC1711_VoltageReg16bitToVoltage_mV(VsenseReg, IsSignedVoltage, VsenseScaleRange);
    IsenseReal = ( VsenseReal * 1000000.0 ) / (float)(rsense);
    return IsenseReal;
}


float PAC1711_VpowerReg32bitToPower_mW(uint32_t VpowerReg, _Bool IsSignedPower, uint16_t VPowerScaleRange, uint32_t rsense){
    float VpowerReal, PowerUnit;

    if(rsense == 0) return 0.0;

    if(IsSignedPower == 1){
        int32_t signedVpowerReg;
        signedVpowerReg = (int32_t)VpowerReg;
        VpowerReal = (float)signedVpowerReg;
    }else{
        VpowerReal = (float)VpowerReg;
    }

    PowerUnit = (float)VPowerScaleRange * (1000000.0 / 4294967296.0) / (float)rsense;
    VpowerReal = VpowerReal * PowerUnit;
    return VpowerReal;
}


void PAC1711_Reg16bitToRawBytes(uint16_t regVal, uint8_t* pRawBytes){
    pRawBytes[0] = (regVal >> 8) & 0xff;
    pRawBytes[1] = regVal & 0xff;
}


uint16_t PAC1711_RawBytestoReg16bit(uint8_t* pRawBytes){
    uint16_t regVal;
    regVal = (uint16_t)pRawBytes[0];
    regVal = (regVal << 8) | (uint16_t)pRawBytes[1];
    return regVal;
}


uint32_t PAC1711_RawBytestoReg32bit(uint8_t* pRawBytes){
    uint32_t regVal;
    regVal = (uint32_t)pRawBytes[0];
    regVal = (regVal << 8) | (uint32_t)pRawBytes[1];
    regVal = (regVal << 8) | (uint32_t)pRawBytes[2];
    regVal = (regVal << 8) | (uint32_t)pRawBytes[3];
    return regVal;
}


uint64_t PAC1711_RawBytesToReg64bit(uint8_t* pRawBytes){
    uint64_t regVal;
    regVal = (uint64_t)pRawBytes[0];
    regVal = (regVal << 8) | (uint64_t)pRawBytes[1];
    regVal = (regVal << 8) | (uint64_t)pRawBytes[2];
    regVal = (regVal << 8) | (uint64_t)pRawBytes[3];
    regVal = (regVal << 8) | (uint64_t)pRawBytes[4];
    regVal = (regVal << 8) | (uint64_t)pRawBytes[5];
    regVal = (regVal << 8) | (uint64_t)pRawBytes[6];
    return regVal;
}


_Bool PAC1711_IsSignedVbus(PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr){

    return ( negpwrfsr.CFG_VB !=0 );
}


_Bool PAC1711_IsSignedVsense(PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr){

    return ( negpwrfsr.CFG_VS !=0 );
}


_Bool PAC1711_IsSignedVpower(PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr){

    return ( (negpwrfsr.CFG_VB | negpwrfsr.CFG_VS) != 0 );
}


uint16_t PAC1711_VbusScaleRange(uint16_t VbusMAX, PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr){
    if (negpwrfsr.CFG_VB == 0x1) {
        VbusMAX *= 2;
    }
    return VbusMAX;
}


uint16_t PAC1711_VsenseScaleRange(uint16_t VsenseMax, PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr){
    if (negpwrfsr.CFG_VS == 0x1) {
        VsenseMax *= 2;
    }
    return VsenseMax;
}


uint16_t PAC1711_VpowerScaleRange(uint16_t VPowerMax, PAC1711_NEGPWRFSR_REGFIELDS negpwrfsr){
    if ((negpwrfsr.CFG_VB | negpwrfsr.CFG_VS) == 0x1) {
        VPowerMax *= 2;

    }
    return VPowerMax;
}


float PAC1711_VaccPowerToEnergy_mWh(float accumulatedPower_mW, int16_t sampleRate){
    float Energy;
    if( sampleRate > 1 ) {

        Energy = accumulatedPower_mW / (float)sampleRate;
    }else{
        Energy = 0.0;
    }
    Energy *= (float)1/3600;
    return Energy;
 }


float PAC1711_VaccPowerTimedToEnergy_mWh(float accumulatedPower_mW, uint32_t sampleCount, uint32_t time_ms){
    float Energy;
    if(sampleCount > 0) {
        Energy = accumulatedPower_mW / (float)sampleCount;
    }else{
        Energy = 0.0;
    }

    Energy *= (float)time_ms;
    Energy *= ((float)1/3600 / 1000.0);
    return Energy;
}


float PAC1711_VaccVoltageToCoulombCnt(float accumulatedVoltage_mV, int16_t sampleRate, uint32_t rsense){
    float CoulombCnt;
    if(rsense == 0) return 0.0;

    if( sampleRate > 1 ) {

        CoulombCnt = accumulatedVoltage_mV / (float)sampleRate;
    }else{
        CoulombCnt = 0.0;
    }

    CoulombCnt = (1000000.0 * CoulombCnt) / (float)rsense;
    return CoulombCnt;
}


float PAC1711_VaccVoltageTimedToCoulombCnt(float accumulatedVoltage_mV, uint32_t sampleCount, uint32_t time_ms, uint32_t rsense){
    float CoulombCnt;
    if(rsense == 0) return 0.0;

    if(sampleCount > 0){
        CoulombCnt = accumulatedVoltage_mV / (float)sampleCount;
    }else{
        CoulombCnt = 0.0;
    }

    CoulombCnt *= (float)time_ms * 1000.0 / (float)rsense;
    return CoulombCnt;
}


float PAC1711_CLimitRegisterToCurrent_mA(uint8_t limitRegister, uint16_t VsenseMAX, uint32_t rsense){
    int8_t signedReg;
    int32_t tempProd;
    float limitReal;

    if(rsense == 0) return 0.0;

    signedReg = (int8_t)limitRegister;
    tempProd = (int32_t)signedReg * (int32_t)VsenseMAX;
    limitReal = (float)tempProd * (1000000.0 / 128.0) / (float)rsense;
    return limitReal;
}


float PAC1711_PLimitRegisterToPower_mW(uint16_t limitRegister, uint16_t VPowerMAX, uint32_t rsense){
    int16_t signedReg;
    float PowerUnit;
    float limitReal;

    if(rsense == 0) return 0.0;

    signedReg = (int16_t)limitRegister;
    PowerUnit = (float)VPowerMAX * (1000000.0 / 32768.0) / (float)rsense;
    limitReal = (float)signedReg * PowerUnit;
    return limitReal;
}


float PAC1711_VLimitRegisterToVoltage_mV(uint8_t limitRegister, uint16_t VbusMAX){
    int8_t signedReg;
    int32_t tempProd;
    float limitReal;

    signedReg = (int8_t)limitRegister;
    tempProd = (int32_t)signedReg * (int32_t)VbusMAX;
    limitReal = (float)tempProd / 128.0;
    return limitReal;
}


uint16_t PAC1711_Plimit_mWtoRegisterVal(float PowerLimit, uint16_t VPowerMAX, uint32_t rsense){
    uint16_t limitRegister;
    float maxLimit;
    float flimit;
    int16_t ilimit;

    if( (rsense == 0) || (VPowerMAX == 0) ) return 0;


    maxLimit = (float)VPowerMAX * 1000000;
    maxLimit /= (float)rsense;

    if(PowerLimit >= maxLimit){


        limitRegister = 0x7fff;
    }else if(PowerLimit < (-maxLimit)){


        limitRegister = 0x8000;
    }else{

        flimit = PowerLimit * 32768.0 / maxLimit;
        ilimit = (int16_t)flimit;
        limitRegister = (uint16_t)ilimit;
    }
    return limitRegister;
}


uint8_t PAC1711_Climit_mAtoRegisterVal(float CurrentLimit, uint16_t VsenseMAX, uint32_t rsense){
    uint8_t limitRegister;
    float maxLimit;
    float flimit;
    int8_t ilimit;

    if( (rsense == 0) || (VsenseMAX == 0) ) return 0;


    maxLimit = (float)VsenseMAX * 1000000;
    maxLimit /= (float)rsense;

    if(CurrentLimit >= maxLimit){


        limitRegister = 0x7f;
    }else if(CurrentLimit < (-maxLimit)){


        limitRegister = 0x80;
    }else{

        flimit = CurrentLimit * 128.0 / maxLimit;
        ilimit = (int8_t)flimit;
        limitRegister = (uint8_t)ilimit;
    }
    return limitRegister;
}


uint8_t PAC1711_Vlimit_mVtoRegisterVal(float VoltageLimit, uint16_t VbusMAX){
    uint8_t limitRegister;
    float maxLimit;
    float flimit;
    int8_t ilimit;

    if(VbusMAX == 0) return 0;


    maxLimit = (float)VbusMAX;

    if(VoltageLimit >= maxLimit){


        limitRegister = 0x7f;
    }else if(VoltageLimit < (-maxLimit)){


        limitRegister = 0x80;
    }else{

        flimit = VoltageLimit * 128.0 / maxLimit;
        ilimit = (int8_t)flimit;
        limitRegister = (uint8_t)ilimit;
    }
    return limitRegister;
}
