/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define ADC_IN_TRIS                 TRISAbits.TRISA0
#define ADC_IN_LAT                  LATAbits.LATA0
#define ADC_IN_PORT                 PORTAbits.RA0
#define ADC_IN_WPU                  WPUAbits.WPUA0
#define ADC_IN_OD                   ODCONAbits.ODCA0
#define ADC_IN_ANS                  ANSELAbits.ANSELA0
#define ADC_IN_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define ADC_IN_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define ADC_IN_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define ADC_IN_GetValue()           PORTAbits.RA0
#define ADC_IN_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define ADC_IN_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define ADC_IN_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define ADC_IN_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define ADC_IN_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define ADC_IN_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define ADC_IN_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define ADC_IN_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA2 aliases
#define DAC_OUT_AFE_OFFSET_TRIS                 TRISAbits.TRISA2
#define DAC_OUT_AFE_OFFSET_LAT                  LATAbits.LATA2
#define DAC_OUT_AFE_OFFSET_PORT                 PORTAbits.RA2
#define DAC_OUT_AFE_OFFSET_WPU                  WPUAbits.WPUA2
#define DAC_OUT_AFE_OFFSET_OD                   ODCONAbits.ODCA2
#define DAC_OUT_AFE_OFFSET_ANS                  ANSELAbits.ANSELA2
#define DAC_OUT_AFE_OFFSET_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define DAC_OUT_AFE_OFFSET_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define DAC_OUT_AFE_OFFSET_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define DAC_OUT_AFE_OFFSET_GetValue()           PORTAbits.RA2
#define DAC_OUT_AFE_OFFSET_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define DAC_OUT_AFE_OFFSET_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define DAC_OUT_AFE_OFFSET_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define DAC_OUT_AFE_OFFSET_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define DAC_OUT_AFE_OFFSET_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define DAC_OUT_AFE_OFFSET_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define DAC_OUT_AFE_OFFSET_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define DAC_OUT_AFE_OFFSET_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RB0 aliases
#define CS_SHARP_TRIS                 TRISBbits.TRISB0
#define CS_SHARP_LAT                  LATBbits.LATB0
#define CS_SHARP_PORT                 PORTBbits.RB0
#define CS_SHARP_WPU                  WPUBbits.WPUB0
#define CS_SHARP_OD                   ODCONBbits.ODCB0
#define CS_SHARP_ANS                  ANSELBbits.ANSELB0
#define CS_SHARP_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define CS_SHARP_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define CS_SHARP_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define CS_SHARP_GetValue()           PORTBbits.RB0
#define CS_SHARP_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define CS_SHARP_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define CS_SHARP_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define CS_SHARP_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define CS_SHARP_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define CS_SHARP_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define CS_SHARP_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define CS_SHARP_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 aliases
#define SPI1_SDO1_TRIS                 TRISBbits.TRISB1
#define SPI1_SDO1_LAT                  LATBbits.LATB1
#define SPI1_SDO1_PORT                 PORTBbits.RB1
#define SPI1_SDO1_WPU                  WPUBbits.WPUB1
#define SPI1_SDO1_OD                   ODCONBbits.ODCB1
#define SPI1_SDO1_ANS                  ANSELBbits.ANSELB1
#define SPI1_SDO1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SPI1_SDO1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SPI1_SDO1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SPI1_SDO1_GetValue()           PORTBbits.RB1
#define SPI1_SDO1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SPI1_SDO1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SPI1_SDO1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SPI1_SDO1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SPI1_SDO1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define SPI1_SDO1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define SPI1_SDO1_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define SPI1_SDO1_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 aliases
#define SPI1_SCK1_TRIS                 TRISBbits.TRISB2
#define SPI1_SCK1_LAT                  LATBbits.LATB2
#define SPI1_SCK1_PORT                 PORTBbits.RB2
#define SPI1_SCK1_WPU                  WPUBbits.WPUB2
#define SPI1_SCK1_OD                   ODCONBbits.ODCB2
#define SPI1_SCK1_ANS                  ANSELBbits.ANSELB2
#define SPI1_SCK1_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SPI1_SCK1_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SPI1_SCK1_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SPI1_SCK1_GetValue()           PORTBbits.RB2
#define SPI1_SCK1_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SPI1_SCK1_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SPI1_SCK1_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SPI1_SCK1_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SPI1_SCK1_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define SPI1_SCK1_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define SPI1_SCK1_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define SPI1_SCK1_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 aliases
#define SPI1_SDI1_TRIS                 TRISBbits.TRISB3
#define SPI1_SDI1_LAT                  LATBbits.LATB3
#define SPI1_SDI1_PORT                 PORTBbits.RB3
#define SPI1_SDI1_WPU                  WPUBbits.WPUB3
#define SPI1_SDI1_OD                   ODCONBbits.ODCB3
#define SPI1_SDI1_ANS                  ANSELBbits.ANSELB3
#define SPI1_SDI1_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define SPI1_SDI1_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define SPI1_SDI1_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define SPI1_SDI1_GetValue()           PORTBbits.RB3
#define SPI1_SDI1_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define SPI1_SDI1_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define SPI1_SDI1_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define SPI1_SDI1_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define SPI1_SDI1_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define SPI1_SDI1_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define SPI1_SDI1_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define SPI1_SDI1_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 aliases
#define CS_LOOPDRIVER_DIGIPOT_TRIS                 TRISBbits.TRISB4
#define CS_LOOPDRIVER_DIGIPOT_LAT                  LATBbits.LATB4
#define CS_LOOPDRIVER_DIGIPOT_PORT                 PORTBbits.RB4
#define CS_LOOPDRIVER_DIGIPOT_WPU                  WPUBbits.WPUB4
#define CS_LOOPDRIVER_DIGIPOT_OD                   ODCONBbits.ODCB4
#define CS_LOOPDRIVER_DIGIPOT_ANS                  ANSELBbits.ANSELB4
#define CS_LOOPDRIVER_DIGIPOT_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_GetValue()           PORTBbits.RB4
#define CS_LOOPDRIVER_DIGIPOT_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define CS_LOOPDRIVER_DIGIPOT_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 aliases
#define CS_LOOPDRIVER_DAC_TRIS                 TRISBbits.TRISB5
#define CS_LOOPDRIVER_DAC_LAT                  LATBbits.LATB5
#define CS_LOOPDRIVER_DAC_PORT                 PORTBbits.RB5
#define CS_LOOPDRIVER_DAC_WPU                  WPUBbits.WPUB5
#define CS_LOOPDRIVER_DAC_OD                   ODCONBbits.ODCB5
#define CS_LOOPDRIVER_DAC_ANS                  ANSELBbits.ANSELB5
#define CS_LOOPDRIVER_DAC_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define CS_LOOPDRIVER_DAC_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define CS_LOOPDRIVER_DAC_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define CS_LOOPDRIVER_DAC_GetValue()           PORTBbits.RB5
#define CS_LOOPDRIVER_DAC_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define CS_LOOPDRIVER_DAC_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define CS_LOOPDRIVER_DAC_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define CS_LOOPDRIVER_DAC_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define CS_LOOPDRIVER_DAC_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define CS_LOOPDRIVER_DAC_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define CS_LOOPDRIVER_DAC_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define CS_LOOPDRIVER_DAC_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RC0 aliases
#define JS_PUSH_TRIS                 TRISCbits.TRISC0
#define JS_PUSH_LAT                  LATCbits.LATC0
#define JS_PUSH_PORT                 PORTCbits.RC0
#define JS_PUSH_WPU                  WPUCbits.WPUC0
#define JS_PUSH_OD                   ODCONCbits.ODCC0
#define JS_PUSH_ANS                  ANSELCbits.ANSELC0
#define JS_PUSH_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define JS_PUSH_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define JS_PUSH_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define JS_PUSH_GetValue()           PORTCbits.RC0
#define JS_PUSH_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define JS_PUSH_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define JS_PUSH_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define JS_PUSH_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define JS_PUSH_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define JS_PUSH_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define JS_PUSH_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define JS_PUSH_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)
#define RC0_SetInterruptHandler  JS_PUSH_SetInterruptHandler

// get/set RC1 aliases
#define JS_LEFT_TRIS                 TRISCbits.TRISC1
#define JS_LEFT_LAT                  LATCbits.LATC1
#define JS_LEFT_PORT                 PORTCbits.RC1
#define JS_LEFT_WPU                  WPUCbits.WPUC1
#define JS_LEFT_OD                   ODCONCbits.ODCC1
#define JS_LEFT_ANS                  ANSELCbits.ANSELC1
#define JS_LEFT_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define JS_LEFT_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define JS_LEFT_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define JS_LEFT_GetValue()           PORTCbits.RC1
#define JS_LEFT_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define JS_LEFT_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define JS_LEFT_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define JS_LEFT_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define JS_LEFT_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define JS_LEFT_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define JS_LEFT_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define JS_LEFT_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)
#define RC1_SetInterruptHandler  JS_LEFT_SetInterruptHandler

// get/set RC2 aliases
#define JS_UP_TRIS                 TRISCbits.TRISC2
#define JS_UP_LAT                  LATCbits.LATC2
#define JS_UP_PORT                 PORTCbits.RC2
#define JS_UP_WPU                  WPUCbits.WPUC2
#define JS_UP_OD                   ODCONCbits.ODCC2
#define JS_UP_ANS                  ANSELCbits.ANSELC2
#define JS_UP_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define JS_UP_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define JS_UP_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define JS_UP_GetValue()           PORTCbits.RC2
#define JS_UP_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define JS_UP_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define JS_UP_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define JS_UP_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define JS_UP_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define JS_UP_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define JS_UP_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define JS_UP_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)
#define RC2_SetInterruptHandler  JS_UP_SetInterruptHandler

// get/set RC5 aliases
#define JS_DOWN_TRIS                 TRISCbits.TRISC5
#define JS_DOWN_LAT                  LATCbits.LATC5
#define JS_DOWN_PORT                 PORTCbits.RC5
#define JS_DOWN_WPU                  WPUCbits.WPUC5
#define JS_DOWN_OD                   ODCONCbits.ODCC5
#define JS_DOWN_ANS                  ANSELCbits.ANSELC5
#define JS_DOWN_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define JS_DOWN_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define JS_DOWN_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define JS_DOWN_GetValue()           PORTCbits.RC5
#define JS_DOWN_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define JS_DOWN_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define JS_DOWN_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define JS_DOWN_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define JS_DOWN_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define JS_DOWN_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define JS_DOWN_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define JS_DOWN_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)
#define RC5_SetInterruptHandler  JS_DOWN_SetInterruptHandler

// get/set RC6 aliases
#define JS_RIGHT_TRIS                 TRISCbits.TRISC6
#define JS_RIGHT_LAT                  LATCbits.LATC6
#define JS_RIGHT_PORT                 PORTCbits.RC6
#define JS_RIGHT_WPU                  WPUCbits.WPUC6
#define JS_RIGHT_OD                   ODCONCbits.ODCC6
#define JS_RIGHT_ANS                  ANSELCbits.ANSELC6
#define JS_RIGHT_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define JS_RIGHT_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define JS_RIGHT_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define JS_RIGHT_GetValue()           PORTCbits.RC6
#define JS_RIGHT_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define JS_RIGHT_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define JS_RIGHT_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define JS_RIGHT_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define JS_RIGHT_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define JS_RIGHT_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define JS_RIGHT_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define JS_RIGHT_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)
#define RC6_SetInterruptHandler  JS_RIGHT_SetInterruptHandler

// get/set RC7 aliases
#define EIN_SHARP_TRIS                 TRISCbits.TRISC7
#define EIN_SHARP_LAT                  LATCbits.LATC7
#define EIN_SHARP_PORT                 PORTCbits.RC7
#define EIN_SHARP_WPU                  WPUCbits.WPUC7
#define EIN_SHARP_OD                   ODCONCbits.ODCC7
#define EIN_SHARP_ANS                  ANSELCbits.ANSELC7
#define EIN_SHARP_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define EIN_SHARP_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define EIN_SHARP_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define EIN_SHARP_GetValue()           PORTCbits.RC7
#define EIN_SHARP_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define EIN_SHARP_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define EIN_SHARP_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define EIN_SHARP_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define EIN_SHARP_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define EIN_SHARP_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define EIN_SHARP_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define EIN_SHARP_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the JS_PUSH pin functionality
 * @param none
 * @return none
 */
void JS_PUSH_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for JS_PUSH pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for JS_PUSH at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void JS_PUSH_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for JS_PUSH pin.
 *        This is a dynamic interrupt handler to be used together with the JS_PUSH_SetInterruptHandler() method.
 *        This handler is called every time the JS_PUSH ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*JS_PUSH_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for JS_PUSH pin. 
 *        This is a predefined interrupt handler to be used together with the JS_PUSH_SetInterruptHandler() method.
 *        This handler is called every time the JS_PUSH ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void JS_PUSH_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the JS_LEFT pin functionality
 * @param none
 * @return none
 */
void JS_LEFT_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for JS_LEFT pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for JS_LEFT at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void JS_LEFT_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for JS_LEFT pin.
 *        This is a dynamic interrupt handler to be used together with the JS_LEFT_SetInterruptHandler() method.
 *        This handler is called every time the JS_LEFT ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*JS_LEFT_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for JS_LEFT pin. 
 *        This is a predefined interrupt handler to be used together with the JS_LEFT_SetInterruptHandler() method.
 *        This handler is called every time the JS_LEFT ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void JS_LEFT_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the JS_UP pin functionality
 * @param none
 * @return none
 */
void JS_UP_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for JS_UP pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for JS_UP at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void JS_UP_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for JS_UP pin.
 *        This is a dynamic interrupt handler to be used together with the JS_UP_SetInterruptHandler() method.
 *        This handler is called every time the JS_UP ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*JS_UP_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for JS_UP pin. 
 *        This is a predefined interrupt handler to be used together with the JS_UP_SetInterruptHandler() method.
 *        This handler is called every time the JS_UP ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void JS_UP_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the JS_DOWN pin functionality
 * @param none
 * @return none
 */
void JS_DOWN_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for JS_DOWN pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for JS_DOWN at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void JS_DOWN_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for JS_DOWN pin.
 *        This is a dynamic interrupt handler to be used together with the JS_DOWN_SetInterruptHandler() method.
 *        This handler is called every time the JS_DOWN ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*JS_DOWN_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for JS_DOWN pin. 
 *        This is a predefined interrupt handler to be used together with the JS_DOWN_SetInterruptHandler() method.
 *        This handler is called every time the JS_DOWN ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void JS_DOWN_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the JS_RIGHT pin functionality
 * @param none
 * @return none
 */
void JS_RIGHT_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for JS_RIGHT pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for JS_RIGHT at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void JS_RIGHT_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for JS_RIGHT pin.
 *        This is a dynamic interrupt handler to be used together with the JS_RIGHT_SetInterruptHandler() method.
 *        This handler is called every time the JS_RIGHT ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*JS_RIGHT_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for JS_RIGHT pin. 
 *        This is a predefined interrupt handler to be used together with the JS_RIGHT_SetInterruptHandler() method.
 *        This handler is called every time the JS_RIGHT ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void JS_RIGHT_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/