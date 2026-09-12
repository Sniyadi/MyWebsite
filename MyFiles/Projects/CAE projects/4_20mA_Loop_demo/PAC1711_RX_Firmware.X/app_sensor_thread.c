/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_sensor_thread.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include "app_sensor_thread.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_SENSOR_THREAD_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

PAC1711_DEVICE_CONTEXT deviceContext;
PAC1711_DEVICE_INIT deviceInit;
uint32_t rsense = PDB_RSENSE_MICRO_CH1;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

///* RST1 = RA7 on PIC18F57Q43 Curiosity Nano */
//#define RST1_PinOutputEnable()  IO_RA7_SetDigitalOutput()
//#define RST1_PinClear()         IO_RA7_SetLow()
//#define RST1_PinSet()           IO_RA7_SetHigh()
//
///* RST2 = RC7 on PIC18F57Q43 Curiosity Nano */
//#define RST2_PinOutputEnable()  IO_RC7_SetDigitalOutput()
//#define RST2_PinClear()         IO_RC7_SetLow()
//#define RST2_PinSet()           IO_RC7_SetHigh()

/* RST3 = RD5 on PIC18F57Q43 Curiosity Nano */
#define RST3_PinOutputEnable()  IO_RD5_SetDigitalOutput()
#define RST3_PinClear()         IO_RD5_SetLow()
#define RST3_PinSet()           IO_RD5_SetHigh()



/* reset the PAC1711 device by PWRDN toggle */
/* use mikroE RST signal to drive PWRDN pin */
/* assume PIN_MANAGER_Initialize() was already called by SYSTEM_Initialize() call in main(); */
void deviceReset(void){
    RST3_PinOutputEnable();    // configure PIN pin as output
    RST3_PinClear();           // drive RST pin low
    DELAY_milliseconds(10);    // keep RST pin for a little while
    RST3_PinSet();             // drive RST pin high
    DELAY_milliseconds(20);            // The first measurement data may be requested by a
                                       // REFRESH or REFRESH_V command 20 ms after the
                                       // PWRDN pin is pulled high.
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_SENSOR_THREAD_Initialize ( void )

  Remarks:
    See prototype in app_sensor_thread.h.
 */
void APP_SENSOR_THREAD_Initialize(void) 
{
 
    int16_t errorCode = PAC1711_SUCCESS;
    
    /* Place the App state machine in its initial state. */
    
    //reset the PAC device
    deviceReset();
    
    // provide the i2c config parameters
    deviceInit.i2c_init.i2cAddress = PAC1711_CLIENT_ADDRESS;
    //i2c driver functions
    deviceInit.i2c_init.i2cWriteRead           = I2C1_WriteRead;
    deviceInit.i2c_init.i2cWrite               = I2C1_Write;
    deviceInit.i2c_init.i2cTransferStatusGet   = I2C1_IsBusy;
    deviceInit.i2c_init.i2cTransferCallbackSet = NULL;

    // provide the library config parameters
    deviceInit.syncMode = true;    //use the sync mode
    deviceInit.rsense = rsense;

    printf("\n\rPAC1711_Device_Initialize(): ");
    errorCode = PAC1711_Device_Initialize(&deviceContext, deviceInit);
    if (errorCode != PAC1711_SUCCESS){
        printf("fail: %d", errorCode);
    }else{
        printf("done");
    }
}

/******************************************************************************
  Function:
    void APP_SENSOR_THREAD_Tasks ( void )

  Remarks:
    See prototype in app_sensor_thread.h.
 */

void APP_SENSOR_THREAD_Tasks(void) 
{

    if (PAC1711_Device_IsInitialized(&deviceContext) == false){
        printf("\n\rDevice init error. Stop.");
        while(1);
    }
}

            


/*******************************************************************************
 End of File
 */