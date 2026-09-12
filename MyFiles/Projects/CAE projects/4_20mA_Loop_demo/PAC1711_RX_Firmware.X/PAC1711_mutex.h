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

#ifndef PAC1711_MUTEX_H
#define PAC1711_MUTEX_H

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/** @file PAC1711_mutex.h
 * This file implements the MUTEX functions for create, lock and unlock.
 * The MUTEX support functions are platform and OS dependent.
 * Please note that MUTEX functions may be removed from the library 
 * or implemented here as "empty" functions if the library is used 
 * in a single-threaded application (there is no possibility to have 
 * concurrent API function calls to the same device).
 * @attention Platform specific files must be included for using the MUTEX support.
 */    

/* Included Files */
#include <stdbool.h>

    
/** 
 * @typedef PAC1711_MUTEX
 * The PAC1711 library uses a MUTEX object to avoid simultaneous access to device
 * data structures from parallel processing threads. 
 * The MUTEX object type may differ on different platforms.  
 * @attention This type definition must be updated for the target platform .
 */
typedef uint8_t  PAC1711_MUTEX;

/* MUTEX support functions */

/**
 * @brief The function creates the MUTEX object
 * 
 * If the user application is single-threaded, the function may just return "true".
 * @param pmutex [in,out] - Pointer to the mutex object.
 * @return true if mutex object was created, false otherwise.
 */
static inline bool PAC1711_MUTEX_Create(PAC1711_MUTEX *pmutex){
    return true;
}

/**
 * @brief The function locks the MUTEX.
 * 
 * If the user application is single-threaded, the function may just return "true".
 * @param pmutex [in,out] - Pointer to the mutex object.
 * @return true if mutex was locked, false otherwise.
 */
static inline bool PAC1711_MUTEX_Lock(PAC1711_MUTEX *pmutex){
    return true;
}

/**
 * @brief The function un-locks the MUTEX.
 * 
 * @param pmutex [in,out] - Pointer to the mutex object.
 */
static inline void PAC1711_MUTEX_Unlock(PAC1711_MUTEX *pmutex){
    return;
}

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	// _PAC1711_MUTEX_H

/**
  End of File
*/
