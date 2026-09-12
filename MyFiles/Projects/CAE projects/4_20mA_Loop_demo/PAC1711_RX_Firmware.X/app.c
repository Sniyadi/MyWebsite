/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include "app.h"
#include "PAC1711.h"
#include "mcc_generated_files/i2c_host/i2c1.h"  // For I2C1_ErrorGet()
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
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

#define IO_LED_Toggle() IO_RF3_Toggle()
#define WAIT_TICK_MS 100;

APP_DATA appData;

extern PAC1711_DEVICE_CONTEXT deviceContext;

PAC1711_deviceID deviceID;
float voltage, amperage, power, energy;
PAC1711_EVENT lastEvent = PAC1711_EVENT_NONE;
int16_t lastError = PAC1711_SUCCESS;

static void Timer_Callback(void);

static const struct TMR_INTERFACE *Timer = &Timer0; // TODO: Replace Timer0 with name of const struct TMR_INTERFACE, from MCC Generated Files > timer > tmrx.c

static void Timer_Callback(void)
{
    IO_LED_Toggle();
    if((appData.wait_started == true) && 
        (appData.wait_MS > 0)){
        appData.wait_MS -= WAIT_TICK_MS;
    }
}

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

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    Timer->Stop();
    Timer->TimeoutCallbackRegister(Timer_Callback);
    appData.wait_started = false;
    appData.wait_MS = 0;
    Timer->Start();
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    int16_t errorCode = PAC1711_SUCCESS;
    
    /* Check the application's current state. */
    switch ( appData.state ){
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            if(PAC1711_Device_IsInitialized(&deviceContext) == true){
                appData.state = APP_STATE_DEVICE_ID;    // go to next app state
            }
            break;
        }

        
        //DEVICE_ID
        case APP_STATE_DEVICE_ID:
        {
            printf("\n\n\rPAC1711_GetDeviceID(): ");
            errorCode = PAC1711_GetDeviceID(&deviceContext, &deviceID);
            if (errorCode == PAC1711_SUCCESS ){
                printf("\n\r ProductID: %Xh", deviceID.product);
                printf("\n\r ManufacturerID: %Xh", deviceID.manufacturer);
                printf("\n\r RevisionID: %Xh", deviceID.revision);
                
                appData.state = APP_STATE_REFRESH;  // go to next app state
            }else{
                printf("fail: %d", errorCode);
            }
            break;
        }
        
        
        //REFRESH
        case APP_STATE_REFRESH:
        {
            printf("\n\n\r PAC1711_RefreshV(): ");
            errorCode = PAC1711_RefreshV(&deviceContext);
            if (errorCode == PAC1711_SUCCESS && !I2C1_IsBusy()){
            //if (errorCode == PAC1711_SUCCESS){
                printf("Refresh done");
                DELAY_milliseconds(200); //wait for data to settle
                appData.state = APP_STATE_READ_VBUS;    // go to next app state
            }else{
                printf("fail: %d", errorCode);
            }
            break;
        }
        
        
        //VBUS
        case APP_STATE_READ_VBUS:
        {
            printf("\n\r PAC1711_GetVSENSE_mV(): ");
            errorCode = PAC1711_GetVSENSE_mV(&deviceContext, &voltage);                      //PAC1711_GetVBUS_mV - we were calculating vbus here which is nto valid for 8 pins
            if (errorCode == PAC1711_SUCCESS && !I2C1_IsBusy()){
            //if (errorCode == PAC1711_SUCCESS){
                printf("%f", voltage);
                 DELAY_milliseconds(50);        //ADDED FOR TESTING PURPOSE
                appData.state = APP_STATE_READ_VSENSE;  // go to next app state                
            }else{
                printf("fail: %d", errorCode);
            } 
            break;
        } 
        
        case APP_STATE_READ_VSENSE:
        {
         printf("\n\r PAC1711_GetISENSE_mA(): ");
            errorCode = PAC1711_GetISENSE_mA(&deviceContext, &amperage);
            if (errorCode == PAC1711_SUCCESS && !I2C1_IsBusy()){
            //if (errorCode == PAC1711_SUCCESS){

                if(amperage >= 3.0 && amperage <= 22.0){
                  printf("%f", amperage);
               }else{
                   printf("OUT OF RANGE: %f", amperage); }
                //printf("%f", amperage);
                DELAY_milliseconds(2);
                appData.state = APP_STATE_WAIT  ;              //APP_STATE_READ_POWER   // go to next app state
            }else{
                printf("fail: %d", errorCode);
            }
            break;
        }
   
        //POWER
        case APP_STATE_READ_POWER:
        {
            printf("\n\r PAC1711_GetVPOWER_mW(): ");
            errorCode = PAC1711_GetVPOWER_mW(&deviceContext, &power);
            if (errorCode == PAC1711_SUCCESS){
                printf("%f", power);  
                DELAY_milliseconds(2);  
                appData.state = APP_STATE_READ_ENERGY;  // go to next app state
            }else{
                printf("fail: %d", errorCode);
            }
            break;
        }
        
        
        //ENERGY
        case APP_STATE_READ_ENERGY:
        {
            printf("\n\r PAC1711_GetEnergy_mWh(): ");
            errorCode = PAC1711_GetEnergy_mWh(&deviceContext, &energy);
            if (errorCode == PAC1711_SUCCESS){
                printf("%f", energy);
                DELAY_milliseconds(2);  
                appData.state = APP_STATE_WAIT; // go to next app state
            }else{
                printf("fail: %d", errorCode);
            }
            break;
        }
        
        
        //WAIT
        case APP_STATE_WAIT:{
            if(appData.wait_started == false){
                //start the "wait counter"
                appData.wait_MS = WAIT_MS;
                appData.wait_started = true;
                printf("\n\rWait %ld ms:", appData.wait_MS);
            }else{
                //check the wait time expiration
                if(appData.wait_MS <= 0){
                    //stop the "wait counter"
                    appData.wait_started = false;
                    printf("\n\r wait time done");
                    appData.state = APP_STATE_REFRESH;  //go to next app state                
                }
            }
            break;
        }
            
        /* The default state should never be executed. */
        default:
        {
            printf("\n\rRestart App");
            appData.state = APP_STATE_INIT; //start over            
            break;
        }
    }
    
    /* other application tasks */
    //was the device busy?
    if( errorCode == PAC1711_BUSY ) printf(" \n\rdevice busy!");
    
    //device last event check
    errorCode = PAC1711_GetEventStatus(&deviceContext, &lastEvent, &lastError);
    if(errorCode != PAC1711_SUCCESS){
        printf("\n\n\rPAC1711_GetEventStatus() fail");
    }else{
        if(lastEvent == PAC1711_EVENT_REQUEST_FAIL){
            printf("\n\n\rLast event: %d, Last error %d", lastEvent, lastError);
        }
    }    

}


/*******************************************************************************
 End of File
 */
