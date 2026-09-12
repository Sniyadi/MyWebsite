/*
  (c) 2026 Microchip Technology Inc. and its subsidiaries

  Subject to your compliance with these terms, you may use this Microchip 
  software and any derivatives of this software. You must retain the above
  copyright notice with any redistribution of this software and the following
  disclaimers. It is your responsibility to comply with third party license
  terms applicable to your use of third party software (including open source
  software) that may accompany this Microchip software. THIS SOFTWARE IS
  SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR
  STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF 
  NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
  WHATSOEVER RELATED TO THIS SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
  IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF
  ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*/

#ifndef PAC1711_I2C_H
#define PAC1711_I2C_H

/** @file PAC1711_i2c.h
 * This file implements the device communication functions over i2c interface
 * and the associated data types and data structures.
 * The I2C support functions are platform and OS dependent. 
 * @attention Platform specific files must be included for using the I2C support.
 *
 * PAC1711 library defines here a "generic" I2C API:
 * - PAC1711_I2C_Initialize()              - Setup the I2C communication with the PAC1711 device
 * - PAC1711_I2C_TransferSetup()           - Change the I2C transfer attributes 
 * - PAC1711_I2C_WriteRead()               - Write + Read data transfer with the device
 * - PAC1711_I2C_Write()                   - Write data to the device
 * - PAC1711_I2C_TransferStatusGet()       - Report the data transfer status
 * - PAC1711_I2C_TransferEventHandlerSet() - Register the I2C transfer event callback function
 */    
    
/*
 *   Section: Included Files
 */

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Platform specific I2C driver support
#include "mcc_generated_files/i2c_host/i2c1.h"
    
/*
 * Target platform adaptation data types and services
 */    

/** PAC1711_I2C_HANDLE identifier is associated to a driver instance, which was open by a driver client. 
 * This is used internally by the PAC1711 library (no need for the user application to handle it.)
 * @attention This type is platform specific and may not be implemented by some i2c drivers. 
 */
//PIC18 I2C driver does not implement the driver instance identifier
//typedef DRV_HANDLE PAC1711_I2C_HANDLE;             // uintptr_t

/** PAC1711_I2C_TRANSFER_HANDLE identifier is assigned by the i2c driver 
 * to a pending i2c transfer. This is used internally by the PAC1711 library 
 * (no need for the user application to handle it).
 * @attention This type is platform specific and may not be implemented by some i2c drivers.
 */
//PIC18 I2C driver does not implement the transfer instance identifier
//typedef DRV_I2C_TRANSFER_HANDLE PAC1711_I2C_TRANSFER_HANDLE;    // uintptr_t

/** PAC1711_I2C_TRANSFER_SETUP structure is the input parameter for the function
 * PAC1711_I2C_TransferSetup(). It usually contains the i2c clock rate configuration parameter. 
 * PAC1711 library configures the I2C transfer parameters at the library initialization 
 * but the user application may call PAC1711_I2C_TransferSetup() function anytime to change them.
 * @attention This type is platform specific and may differ among different i2c drivers.
 */
//PIC18 I2C driver does not implement API for I2C transfer setup change
//typedef DRV_I2C_TRANSFER_SETUP  PAC1711_I2C_TRANSFER_SETUP;   

/** pi2c_init->i2cOpen() may return PAC1711_I2C_HANDLE_INVALID in case of failure.
 * @attention The define must be updated according to the platform I2C API. */
//PIC18 I2C driver does not implement the driver instance identifier
//#define PAC1711_I2C_HANDLE_INVALID          DRV_HANDLE_INVALID

/** pi2c_context->i2cWriteRead() and pi2c_context->i2cWrite() may return 
 * PAC1711_I2C_TRANSFER_HANDLE_INVALID in case of failure.
 * @attention The define must be updated according to the platform I2C API. */
//PIC18 I2C driver does not implement the transfer instance identifier
//#define PAC1711_I2C_TRANSFER_HANDLE_INVALID DRV_I2C_TRANSFER_HANDLE_INVALID


/** PAC1711_I2C_TRANSFER_EVENT enum type defines the i2c event identifiers returned 
 * by the i2c transfer functions or reported to the I2C transfer callback function 
 * (if supported by the driver).
 */
typedef enum
{
    /** Transfer request is pending */
    PAC1711_I2C_TRANSFER_EVENT_PENDING = 0,        //DRV_I2C_TRANSFER_EVENT_PENDING,
    /** All data from or to the buffer was transferred successfully. */
    PAC1711_I2C_TRANSFER_EVENT_COMPLETE = 1,       //DRV_I2C_TRANSFER_EVENT_COMPLETE,
    /** Transfer Handle given is expired. It means transfer
        is completed but with or without error is not known. */            
    PAC1711_I2C_TRANSFER_EVENT_HANDLE_EXPIRED = 2, //DRV_I2C_TRANSFER_EVENT_HANDLE_EXPIRED, 
    /** There was an error while processing the buffer transfer request. */
    PAC1711_I2C_TRANSFER_EVENT_ERROR = 3,          //DRV_I2C_TRANSFER_EVENT_ERROR,
    PAC1711_I2C_TRANSFER_EVENT_HANDLE_INVALID = 4, //DRV_I2C_TRANSFER_EVENT_HANDLE_INVALID,
    /* additional event codes */
    PAC1711_I2C_TRANSFER_NO_EVENT = 100
} PAC1711_I2C_TRANSFER_EVENT, *PAC1711_I2C_TRANSFER_EVENT_P;


/** 
 * @brief I2C event callback function type.
 * 
 * The I2C event handler function is implemented by the PAC1711 device library and is  
 * called by the I2C communication adaptation layer if the platform I2C driver 
 * supports the registration of callback event handlers.
 * The library event handler function is registered to the I2C adaptation layer by the 
 * call of the PAC1711_I2C_TransferEventHandlerSet() function.
 * Note: If the platform I2C driver has no callback support, the library checks the 
 * status of the I2C communication using PAC1711_I2C_TransferStatusGet() then calls the event handler.
 * @param event [in] - PAC1711_I2C_TRANSFER_EVENT type
 * @param context [in] - uintptr_t type pointer to the object registered by the library, 
 *                       returned back to the library by the event handler call.
 */
typedef void ( *PAC1711_I2C_TRANSFER_EVENT_HANDLER_P )( PAC1711_I2C_TRANSFER_EVENT event, uintptr_t context );


/** 
 * @brief Pointer type to the I2C Open function.
 * 
 * The I2C Open function is implemented on some platforms by the I2C drivers   
 * and must be called to initiate the I2C communication.
 * The parameter list and the parameters types are platform specific.
 * As an example, the parameter list may contain an I2C bus index and the access attributes. 
 * The function usually returns a handle which must be provided as parameter to other I2C functions.
 * 
 * @attention The typedef must be updated according to the platform I2C API
 */
//PIC18 I2C driver does not implement the instance "Open" API
//typedef DRV_HANDLE (*DRV_I2C_Open_P)(const SYS_MODULE_INDEX, const DRV_IO_INTENT);


/** 
 * @brief Pointer type to the I2C WriteRead transfer function.
 * 
 * The I2C WriteRead function starts an I2C write sequence followed by an I2C read sequence. 
 * The function execution is platform specific, 
 * it may return after the I2c transfer is completed or immediately.
 * 
 * @attention The typedef must be updated according to the platform I2C API
 */
typedef bool (*DRV_I2C_WriteReadTransferAdd_P)(
        uint16_t, 
        uint8_t*, 
        size_t, 
        uint8_t*, 
        size_t 
);


/** 
 * @brief Pointer type to the I2C Write transfer function.
 * 
 * The I2C Write function starts an I2C write sequence. 
 * The function execution is platform specific, 
 * it may return after the I2c transfer is completed or immediately.
 * 
 * @attention The typedef must be updated according to the platform I2C API
 */
typedef bool (*DRV_I2C_WriteTransferAdd_P)(
        uint16_t,
        uint8_t*,
        size_t
);


/** 
 * @brief Pointer type to the I2C transfer parameters setup function.
 * 
 * The function implementation is platform specific. 
 * For example, it may let the caller change the transfer baudrate (I2C clock frequency).
 * 
 * @attention The typedef must be updated according to the platform I2C API
 */
//PIC18 I2C driver does not implement API for I2C transfer setup change
//typedef bool (*DRV_I2C_TransferSetup_P)( const DRV_HANDLE, DRV_I2C_TRANSFER_SETUP*);


/** 
 * @brief Pointer type to the I2C transfer status query function.
 * 
 * The function implementation is platform specific. 
 * For example, it may return the last I2C event type.
 * 
 * @attention The typedef must be updated according to the platform I2C API
 */
typedef bool (* DRV_I2C_TransferStatusGet_P)(void);


/** 
 * @brief Pointer type to the I2C transfer event callback registration function.
 * 
 * The function implementation is platform specific. 
 * For example, it may require as parameter the "I2C handle" returned by the "open" function.
 * 
 * @remark Some platforms may not implement support for I2C event callback, hence
 * they will have no callback registration function. This implies that the I2C communication 
 * is synchronous (the communication functions return when the communication 
 * is completed or in case of error). The PAC1711 library can handle this scenario also.
 * 
 * @attention The typedef must be updated according to the platform I2C API
 */
typedef void (*DRV_I2C_TransferEventHandler_P)(void);
typedef void (*DRV_I2C_TransferEventHandlerSet_P)(
               DRV_I2C_TransferEventHandler_P);

/** @struct _PAC1711_I2C_INIT 
 * @brief _PAC1711_I2C_INIT structure type parameter for the PAC1711_I2C_Initialize() function.
 * 
 * The structure must contain the initialization values for various I2C attributes and members 
 * of the _PAC1711_I2C_CONTEXT structure.
 * - i2cAddress:
 *      + I2C 7-bit device address 
 * - drvIndex:
 *      + I2C bus index. On some platforms it indicates which I2C bus/controller
 *        must be initialized and "open" for communication 
 *        (PAC1711_I2C_Initialize() calls the driver "open" function). 
 *        On other platforms it may not exist.
 *      + *This property is platform specific.*
 * - setup:
 *      + I2C communication parameters. On some platforms this is a structure 
 *        containing the i2c baude-rate setting.
 *      + *This property is platform specific.*
 * - i2cOpen:
 *      + Pointer to the i2c driver "open" function. 
 *        The "Open" function is called by the PAC1711_I2C_Initialize().
 *      + It must be set to NULL if the platform i2c driver does not implement the "Open" function. 
 *      + *This property is platform specific.*
 * - i2cWriteRead:
 *      + Pointer to the i2c driver "WriteRead" function. 
 *      + The platform i2c "WriteRead" function must be supported. 
 *        It typically implements the i2c "read" operations.
 *      + *This property is platform specific.*
 * - i2cWrite:
 *      + Pointer to the i2c driver "Read" function. 
 *      + The platform i2c "Write" function must be supported.
 *        It typically implements the  i2c "write" operations.
 *      + *This property is platform specific.*
 * - i2cTransferSetup:
 *      + Pointer to the i2c driver "TransferSetup" function. 
 *      + The platform i2c "i2cTransferSetup" function may not be supported.
 *        It must be set to NULL if the platform i2c driver does not implement 
 *        the "TransferSetup" function.
 *      + *This property is platform specific.*
 * - i2cTransferStatusGet:
 *      + Pointer to the i2c transfer "StatusGet" function. 
 *      + If "StatusGet" function is not supported by the i2c driver, 
 *        then it must support the event handler callback and the callback registration function. 
 *      + *This property is platform specific.*
 * - i2cTransferCallbackSet:
 *      + Pointer to the i2c transfer event "callback registration" function. 
 *      + If the "callback registration" function is not supported by the i2c driver, 
 *        then it must support the i2c "transfer status query" function. 
 *      + *This property is platform specific.*
 */
typedef struct _PAC1711_I2C_INIT{
    uint16_t                            i2cAddress;             /**< I2C 7-bit device address  */
//  SYS_MODULE_INDEX                    drvIndex;               /**< I2C bus index. 
//                                                                  @attention This property is platform specific. */
//  PAC1711_I2C_TRANSFER_SETUP          setup;                  /**< I2C communication parameters. 
//                                                                   @attention This property is platform specific. */
    //pointers to i2c driver functions
//  DRV_I2C_Open_P                      i2cOpen;                /**< Pointer to the i2c "Open" function, or NULL 
//                                                                  @attention This property is platform specific. */
    DRV_I2C_WriteReadTransferAdd_P      i2cWriteRead;           /**< Pointer to the i2c "WriteRead" function 
                                                                    @attention This property is platform specific. */
    DRV_I2C_WriteTransferAdd_P          i2cWrite;               /**< Pointer to the i2c "Write" function 
                                                                    @attention This property is platform specific. */
//  DRV_I2C_TransferSetup_P             i2cTransferSetup;       /**< Pointer to the i2c "TransferSetup" function, or NULL 
//                                                                  @attention This property is platform specific. */
    DRV_I2C_TransferStatusGet_P         i2cTransferStatusGet;   /**< Pointer to the i2c "StatusGet" function, or NULL 
                                                                    @attention This property is platform specific. */
    DRV_I2C_TransferEventHandlerSet_P i2cTransferCallbackSet;   /**< Pointer to the i2c transfer event callback "registration" function, or NULL 
                                                                    @attention This property is platform specific. */
}PAC1711_I2C_INIT, *PAC1711_I2C_INIT_P;


/** @struct _PAC1711_I2C_CONTEXT
 * @brief _PAC1711_I2C_CONTEXT structure type holds the I2C related attributes for one PAC17xx device
 * 
 * The structure is initialized by the PAC1711_I2C_Initialize() function using the configuration
 * values provisioned with PAC1711_I2C_INIT parameter.
 * - i2cAddress:
 *      + I2C 7-bit device address 
 * - pi2cEventHandler:
 *      + the pointer to the PAC1711 library callback function for the i2c transfer events,
 *        called by PAC1711_I2CDRV_EventHandler().
 *      + If the I2C driver does not support the events callback, 
 *        the events are polled and handled by the library directly. 
 * - pi2cEventHandlerContext:
 *      + the pointer to the object registered by the PAC1711_I2C_TransferEventHandlerSet() call, 
 *        which is returned back to the library by the event handler callback.
 * - i2cEventCallbackRegistered:
 *      + true if a callback function was registered (pi2cEventHandler not NULL) for the i2c transfer events,
 *        false otherwise.
 * - i2cHandle:
 *      + The handle returned by the "Open" function, if implemented by the i2c driver.
 *      + *This property is platform specific.*
 * - i2cTransferHandle:
 *      + The handle returned by the calls to the i2c driver transfer functions"WriteRead" and "Write". 
 *      + *This property is platform specific.*
 * - i2cWriteRead: 
 *      + Pointer to the i2c driver "WriteRead" function.
 *      + The platform i2c "WriteRead" function must be supported. It typically implements the i2c "read" operations.
 *      + *This property is platform dependent.*
 * - i2cWrite:
 *      + Pointer to the i2c driver "Read" function. 
 *      + The platform i2c "Write" function must be supported.It typically implements the  i2c "write" operations.
 *      + *This property is platform dependent.* 
 * - i2cTransferSetup:
 *      + Pointer to the i2c driver "TransferSetup" function. 
 *      + The platform i2c "i2cTransferSetup" function may not be supported. 
 *        It must be set to NULL if the platform i2c driver does not implement the "TransferSetup" function.
 *      + *This property is platform dependent.*
 * - i2cTransferStatusGet:
 *      + Pointer to the i2c transfer "StatusGet" function. 
 *      + If "StatusGet" function is not supported by the i2c driver, 
 *        then it must support the event handler callback and the callback registration function. 
 *      + *This property is platform dependent.*
 * - i2cTransferCallbackSet:
 *      + Pointer to the i2c transfer event "callback registration" function. 
 *      + If the "callback registration" function is not supported by the i2c driver, 
 *        then it must support the i2c "transfer status query" function. 
 *      + *This property is platform dependent.*
 */
typedef struct _PAC1711_I2C_CONTEXT{
    uint16_t                                i2cAddress;                 /**< I2C 7-bit device address  */
    PAC1711_I2C_TRANSFER_EVENT_HANDLER_P    pi2cEventHandler;           /**< Callback function for the I2C transfer events */
    uintptr_t                               pi2cEventHandlerContext;    /**< Context object returned to the callback function */
    bool                                    i2cEventCallbackRegistered; /**< Indication that callback function is registered */
    //i2c driver dependent handles
//  PAC1711_I2C_HANDLE                      i2cHandle;                  /**< The handle returned by the "Open" function 
//                                                                          @attention This property is platform specific. */
//  PAC1711_I2C_TRANSFER_HANDLE             i2cTransferHandle;          /**< I2C transfer handle returned by "WriteRead" and "Write" functions
//                                                                          @attention This property is platform specific. */
    //pointers to i2c driver functions
    DRV_I2C_WriteReadTransferAdd_P          i2cWriteRead;               /**< Pointer to the i2c "WriteRead" function 
                                                                            @attention This property is platform specific. */
    DRV_I2C_WriteTransferAdd_P              i2cWrite;                   /**< Pointer to the i2c "Write" function 
                                                                            @attention This property is platform specific. */
//  DRV_I2C_TransferSetup_P                 i2cTransferSetup;           /**< Pointer to the i2c "TransferSetup" function, or NULL 
//                                                                          @attention This property is platform specific. */
    DRV_I2C_TransferStatusGet_P             i2cTransferStatusGet;       /**< Pointer to the i2c "StatusGet" function, or NULL 
                                                                            @attention This property is platform specific. */
    DRV_I2C_TransferEventHandlerSet_P       i2cTransferCallbackSet;     /**< Pointer to the i2c transfer event callback "registration" function, or NULL 
                                                                            @attention This property is platform specific. */
}PAC1711_I2C_CONTEXT, *PAC1711_I2C_CONTEXT_P;


/*
 * Target platform adaptation functions 
 */

/** 
 * @brief Change the I2C transfer attributes
 * 
 * This is a platform specific function. The function calls the I2C driver specific function
 * which makes it possible to change the I2C communication parameters (e.g. the baudrate).
 * The function is called by the PAC1711_I2C_Initialize() function but can be also called 
 * by the user application anytime after the PAC1711 library initialization - PAC1711_Device_Initialize()   
 * @param i2c_context [in] - PAC1711_I2C_CONTEXT structure holding the I2C attributes related to one I2C device 
 * @param setup [in] - PAC1711_I2C_TRANSFER_SETUP structure holding the new values for certain i2c attributes
 * @return 
 *  - *true* - if the function call is successful
 *  - *false* - if the driver setup function fails or if the platform driver dos not support it. 
 */
//PIC18 I2C driver does not implement API for I2C transfer setup change
/*
inline bool PAC1711_I2C_TransferSetup( const PAC1711_I2C_CONTEXT i2c_context, PAC1711_I2C_TRANSFER_SETUP *setup ){
    if(i2c_context.i2cTransferSetup != NULL){
        return i2c_context.i2cTransferSetup(i2c_context.i2cHandle, setup);
    }else{
        return false;
    }
}
*/

/**
 * @brief Setup the I2C communication with the PAC1711 device
 * 
 * The function performs the initialization of the device I2C interface attributes,
 * saves in the device's i2c context structure the pointers to the I2C driver functions 
 * which are used by the I2C platform adaptation layer and calls the i2c driver "Open" 
 * and "TransferSetup" function if they are supported by the i2c driver.
 * The function implementation is platform specific.
 * The function is called by the PAC1711 library initialization - PAC1711_Device_Initialize()
 * @param pi2c_context [out] - pointer to the PAC1711_I2C_CONTEXT structure allocated for the PAC1711 device
 * @param i2c_init     [in]  - PAC1711_I2C_INIT structure, provisioned by the user application 
 *                             with the necessary initialization values.
 * @return 
 *  - *true* - if the function call is completed successfully
 *  - *false* - if the pi2c_context is NULL
 *  - *false* - if i2c_init.i2cWriteRead or i2c_init.i2cWrite are NULL
 *  - *false* - if i2c_init.i2cTransferStatusGet and i2c_init.i2cTransferCallbackSet are both NULL 
 *  - *false* - in case of failed calls to other i2c driver specific functions (e.g. "Open" and "TransferSetup") 
 */
static inline bool PAC1711_I2C_Initialize( PAC1711_I2C_CONTEXT_P pi2c_context, PAC1711_I2C_INIT i2c_init){
    if( (pi2c_context == NULL) ||
        (i2c_init.i2cWriteRead == NULL) ||
        (i2c_init.i2cWrite == NULL) ) return false;
    
    // the i2c driver must support at least one of the i2c transfer event status query or event callback functions
    if( (i2c_init.i2cTransferStatusGet == NULL) && (i2c_init.i2cTransferCallbackSet == NULL) ) return false;
    
    // create a new i2cHandle
/*
    if(i2c_init.i2cOpen != NULL){
        pi2c_context->i2cHandle = i2c_init.i2cOpen(i2c_init.drvIndex, DRV_IO_INTENT_READWRITE);
    }else{
        pi2c_context->i2cHandle = 0;
    }
    if(pi2c_context->i2cHandle == PAC1711_I2C_HANDLE_INVALID){
        return false;
    }
*/
    // or get it from the initialization parameters
    // pi2c_context->i2cHandle = i2c_init.i2cHandle;

    pi2c_context->i2cAddress = i2c_init.i2cAddress;

    // set the pointers to i2c driver functions
    pi2c_context->i2cWriteRead           = i2c_init.i2cWriteRead;
    pi2c_context->i2cWrite               = i2c_init.i2cWrite;
//  pi2c_context->i2cTransferSetup       = i2c_init.i2cTransferSetup;
    pi2c_context->i2cTransferStatusGet   = i2c_init.i2cTransferStatusGet;
    pi2c_context->i2cTransferCallbackSet = i2c_init.i2cTransferCallbackSet;
    
    pi2c_context->i2cEventCallbackRegistered = false;

/*   
    if( false == PAC1711_I2C_TransferSetup(*pi2c_context, &i2c_init.setup) ){
        return false;
    }
 */
    return true;
}


/**
 * @brief Report the data transfer status
 * 
 * The function implementation is platform specific.
 * The i2c driver must support a transfer status query method in case that 
 * an i2c transfer event callback function is not supported. 
 * The PAC1711 library uses this function to determine the status of the last i2c transfer
 * in case that i2c event callback is not supported.
 * @param i2c_context [in] - pointer to the PAC1711_I2C_CONTEXT structure allocated for the PAC1711 device
 * @return 
 *  - event ID's as defined by *PAC1711_I2C_TRANSFER_EVENT* enum
 *  - *PAC1711_I2C_TRANSFER_NO_EVENT* - if the i2c_context.i2cTransferStatusGet is NULL
 */
static inline PAC1711_I2C_TRANSFER_EVENT PAC1711_I2C_TransferStatusGet(PAC1711_I2C_CONTEXT i2c_context){
    i2c_host_error_t i2cError;
    if (i2c_context.i2cTransferStatusGet != NULL){
        if(i2c_context.i2cTransferStatusGet() == false){    //not busy
            //get last error 
            i2cError = I2C1_ErrorGet();
            if (i2cError == I2C_ERROR_NONE){
                return PAC1711_I2C_TRANSFER_EVENT_COMPLETE;
            }else{
                return PAC1711_I2C_TRANSFER_EVENT_ERROR;
            }
        }else{
            return PAC1711_I2C_TRANSFER_EVENT_PENDING;   //can be also PAC1711_I2C_TRANSFER_NO_EVENT;
        }
    }else{
        return PAC1711_I2C_TRANSFER_NO_EVENT;
    }
}


/**
 * @brief Write + Read data transfer with the device.
 * 
 * The function starts an I2C write followed by an I2C read. 
 * The function implementation is platform specific. The function may return 
 * after the I2C transfer is completed or it may only initiate the transfer and 
 * return immediately. In case of error, the function returns immediately.
 * The PAC1711 library can determine the completion of the I2C transfer either by
 * registering an I2C event callback (if supported by the i2c driver, 
 * using PAC1711_I2C_TransferEventHandlerSet() ) or by using 
 * PAC1711_I2C_TransferStatusGet() to poll the i2c status.
 * @param pi2c_context [in,out] - pointer to the PAC1711_I2C_CONTEXT structure allocated for the PAC1711 device
 * @param writeBuffer  [in]  - buffer containing the data to be written to PAC1711 device (e.g. the register address)
 * @param writeSize    [in]  - write data length (bytes)
 * @param readBuffer   [out] - buffer containing the data read from the PAC1711 device
 * @param readSize     [in]  - read data length (bytes)
 * @return 
 *  - *true* - if the I2C transfer was completed or if it was started successfully.
 *  - *false* - if the I2C transfer failed
 */
static inline bool PAC1711_I2C_WriteRead (
    PAC1711_I2C_CONTEXT_P pi2c_context,
    void* const writeBuffer,
    const size_t writeSize,
    void* const readBuffer,
    const size_t readSize)
{
    bool retcode = true;
    retcode = (/*(DRV_I2C_WriteReadTransferAdd_P)*/pi2c_context->i2cWriteRead)(pi2c_context->i2cAddress,
                                                                               writeBuffer, writeSize, 
                                                                               readBuffer, readSize);
    return retcode;
};


/**
 * @brief Write data to the device.
 * 
 * The function starts an I2C write transfer. 
 * The function implementation is platform specific. The function may return 
 * after the I2C transfer is completed or it may only initiate the transfer and 
 * return immediately. In case of error, the function returns immediately.
 * The PAC1711 library can determine the completion of the I2C transfer either by
 * registering an I2C event callback (if supported by the i2c driver, 
 * using PAC1711_I2C_TransferEventHandlerSet() ) or by using 
 * PAC1711_I2C_TransferStatusGet() to poll the i2c status.
 * @param pi2c_context [in,out] - pointer to the PAC1711_I2C_CONTEXT structure allocated for the PAC1711 device
 * @param writeBuffer  [in] - buffer containing the data to be written to PAC1711 device
 * @param writeSize    [in] - write data length (bytes)
 * @return 
 *  - *true* - if the I2C transfer was completed or if it was started successfully.
 *  - *false* - if the I2C transfer failed
 */
static inline bool PAC1711_I2C_Write(
    PAC1711_I2C_CONTEXT_P pi2c_context,
    void* const writeBuffer,
    const size_t writeSize)
{
    bool retcode = true;
    retcode = (/*(DRV_I2C_WriteTransferAdd_P)*/ pi2c_context->i2cWrite)(pi2c_context->i2cAddress, 
                                                                        writeBuffer, writeSize);
    return retcode;
}


//typedef void ( *PAC1711_I2C_TRANSFER_EVENT_HANDLER_P )( PAC1711_I2C_TRANSFER_EVENT event, uintptr_t context );
//typedef void ( *DRV_I2C_TRANSFER_EVENT_HANDLER )( DRV_I2C_TRANSFER_EVENT event, DRV_I2C_TRANSFER_HANDLE transferHandle, uintptr_t context );
/**
 * @brief I2C driver specific, transfer event handler function
 * 
 * This function implements the platform specific I2C driver transfer event 
 * callback prototype (if supported). So, this is the callback function which gets 
 * registered by PAC1711_I2C_TransferEventHandlerSet() to the I2C driver,
 * as I2C event callback. 
 * This function process the received parameters and then calls the event callback
 * function implemented by the PAC1711 library, which has a more generic API.
 * @param i2c_event [in] - i2c event ID as defined by the platform I2C driver
 * @param i2c_transferHandle [in] - i2c transfer handle, as defined by the platform I2C driver
 * @param pi2c_context [in] - transparent pointer to the PAC1711_I2C_CONTEXT structure 
 *                            holding the I2C attributes related to one I2C device.
 */
static inline void PAC1711_I2CDRV_EventHandler( void ){
/* !!! the I2C driver support for function callback is useless because it provides no call parameters or context  */
/* !!! even so, the callback is called only on transfer error. It cannot be used to signal the transfer successful termination. */
    return;
}


/**
 * @brief Register the I2C transfer event callback function
 * 
 * This function uses the platform I2C driver specific API to register the 
 * PAC1711_I2CDRV_EventHandler() function as I2C event callback and uses the 
 * device I2C context structure to save the callback function implemented by 
 * the PAC1711 library along with the callback function context parameter.
 * @param pi2c_context [in,out] - pointer to the PAC1711_I2C_CONTEXT structure 
 *                                holding the I2C attributes related to one I2C device.
 * @param eventHandler [in] - pointer to the callback function implemented by 
 *                            the PAC1711 library (PAC1711_I2C_TRANSFER_EVENT_HANDLER_P)
 * @param context [i] - transparent pointer to the context object which is returned 
 *                      back as parameter to the PAC1711 event handler.
 * @return 
 *  - *true* - if the callback is successfully registered with the I2C driver
 *  - *false* - if the pi2c_context->i2cHandle is invalid (PAC1711_I2C_HANDLE_INVALID)
 *  - *false* - if the i2c driver does not support event handler registration
 *    (pi2c_context->i2cTransferCallbackSet is NULL)
 */
static inline bool PAC1711_I2C_TransferEventHandlerSet(
    const PAC1711_I2C_CONTEXT_P pi2c_context,                        //&(pdevice->i2c_context)
    const PAC1711_I2C_TRANSFER_EVENT_HANDLER_P eventHandler,        //PAC1711_I2CEventHandler()
    const uintptr_t context                                         //pdevice
){
/* !!! the I2C driver support for function callback is useless because it provides no call parameters or context  */
/* !!! even so, the callback is called only on transfer error. It cannot be used to signal the transfer successful termination. */
/*
    pi2c_context->pi2cEventHandler = eventHandler;
    pi2c_context->pi2cEventHandlerContext = context;
    if( (pi2c_context->i2cHandle != PAC1711_I2C_HANDLE_INVALID ) &&
        (pi2c_context->i2cTransferCallbackSet != NULL) ){
        pi2c_context->i2cTransferCallbackSet( pi2c_context->i2cHandle, 
                                                (DRV_I2C_TRANSFER_EVENT_HANDLER)PAC1711_I2CDRV_EventHandler, 
                                                (uintptr_t)pi2c_context);
        return true;    //i2c event callback registered with success
    }else{
        return false;   //i2c event callback NOT registered
    }
*/
    return false;
}

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	// _PAC1711_I2C_H

/**
  End of File
*/
