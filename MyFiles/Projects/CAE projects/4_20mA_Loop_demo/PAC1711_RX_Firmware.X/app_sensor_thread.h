/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_sensor_thread.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_SENSOR_THREAD_Initialize" and "APP_SENSOR_THREAD_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_SENSOR_THREAD_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _APP_SENSOR_THREAD_H
#define _APP_SENSOR_THREAD_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/timer/delay.h"
#include "PAC1711.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

#define PAC1711_DUT_TYPE          PAC1711 // PAC1811 //  PAC1821 //PAC1861
#define PAC1711_CLIENT_ADDRESS    0x45    // 0x17    // 0x14    //0x11
//old devices
//   0x10 //both A0 and A1 to VDD pull-up
//   0x14 //A0 to GND and A1 to VDD pull-up
//   0x11 //A0 to VDD pull-up and A1 to GND
//   0x17 //both A0 and A1 to GND    
//new devices
//   0x45 //both A0 and A1 to VDD pull-up
//   0x44 //A0 to GND and A1 to VDD pull-up
//   0x41 //A0 to VDD pull-up and A1 to GND
//   0x40 //both A0 and A1 to GND    

#define APP_SENSOR_I2C_CLOCK_SPEED             400000
#define APP_SENSOR_I2C_SLAVE_ADDR              PAC1711_CLIENT_ADDRESS    

// the value for the click setup with 2.43 r sense resistor for 4-20mA measurement
#define PDB_RSENSE_MICRO_CH1  2430000    //micro-ohms (2.43ohm )          //10000 for 10mohm
// the values for the old PDB
//#define PDB_RSENSE_MICRO_CH1  24900000    //micro-ohms
//#define PDB_RSENSE_MICRO_CH2  49900000    //micro-ohms
//#define PDB_RSENSE_MICRO_CH3  75000000    //micro-ohms
//#define PDB_RSENSE_MICRO_CH4  90900000    //micro-ohms
//the values for the PDB version DT100116
//#define PDB_RSENSE_MICRO_CH1  11000000     //micro-ohms    
//#define PDB_RSENSE_MICRO_CH2  24900000    //micro-ohms
//#define PDB_RSENSE_MICRO_CH3  33000000    //micro-ohms
//#define PDB_RSENSE_MICRO_CH4  49900000    //micro-ohms

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_SENSOR_THREAD_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_SENSOR_THREAD_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_SENSOR_THREAD_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_SENSOR_THREAD_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_SENSOR_THREAD_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_SENSOR_THREAD_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_SENSOR_THREAD_Tasks( void );



#endif /* _APP_SENSOR_THREAD_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

