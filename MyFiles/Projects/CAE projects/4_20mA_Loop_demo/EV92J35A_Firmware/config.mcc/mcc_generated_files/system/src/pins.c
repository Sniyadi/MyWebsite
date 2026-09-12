/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.1.1
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

#include "../pins.h"

void (*JS_PUSH_InterruptHandler)(void);
void (*JS_LEFT_InterruptHandler)(void);
void (*JS_UP_InterruptHandler)(void);
void (*JS_DOWN_InterruptHandler)(void);
void (*JS_RIGHT_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x0;
    /**
    ODx registers
    */
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0xFB;
    TRISB = 0xCC;
    TRISC = 0x7F;
    TRISE = 0x8;

    /**
    ANSELx registers
    */
    ANSELA = 0xFF;
    ANSELB = 0xC0;
    ANSELC = 0x98;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x67;
    WPUE = 0x0;


    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLE = 0x8;

   /**
    RxyI2C | RxyFEAT registers   
    */
    RB1I2C = 0x0;
    RB2I2C = 0x0;
    RC3I2C = 0x0;
    RC4I2C = 0x0;
    /**
    PPS registers
    */
    SPI1SDIPPS = 0xB; //RB3->SPI1:SDI1;
    RB1PPS = 0x1E;  //RB1->SPI1:SDO1;
    RC7PPS = 0x25;  //RC7->NCO1:NCO1;
    SPI1SCKPPS = 0xA;  //RB2->SPI1:SCK1;
    RB2PPS = 0x1D;  //RB2->SPI1:SCK1;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCWP = 0x0;
    IOCWN = 0x0;
    IOCWF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x67;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;

    JS_PUSH_SetInterruptHandler(JS_PUSH_DefaultInterruptHandler);
    JS_LEFT_SetInterruptHandler(JS_LEFT_DefaultInterruptHandler);
    JS_UP_SetInterruptHandler(JS_UP_DefaultInterruptHandler);
    JS_DOWN_SetInterruptHandler(JS_DOWN_DefaultInterruptHandler);
    JS_RIGHT_SetInterruptHandler(JS_RIGHT_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin JS_PUSH
    if(IOCCFbits.IOCCF0 == 1)
    {
        JS_PUSH_ISR();  
    }
    // interrupt on change for pin JS_LEFT
    if(IOCCFbits.IOCCF1 == 1)
    {
        JS_LEFT_ISR();  
    }
    // interrupt on change for pin JS_UP
    if(IOCCFbits.IOCCF2 == 1)
    {
        JS_UP_ISR();  
    }
    // interrupt on change for pin JS_DOWN
    if(IOCCFbits.IOCCF5 == 1)
    {
        JS_DOWN_ISR();  
    }
    // interrupt on change for pin JS_RIGHT
    if(IOCCFbits.IOCCF6 == 1)
    {
        JS_RIGHT_ISR();  
    }
}
   
/**
   JS_PUSH Interrupt Service Routine
*/
void JS_PUSH_ISR(void) {

    // Add custom JS_PUSH code

    // Call the interrupt handler for the callback registered at runtime
    if(JS_PUSH_InterruptHandler)
    {
        JS_PUSH_InterruptHandler();
    }
    IOCCFbits.IOCCF0 = 0;
}

/**
  Allows selecting an interrupt handler for JS_PUSH at application runtime
*/
void JS_PUSH_SetInterruptHandler(void (* InterruptHandler)(void)){
    JS_PUSH_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for JS_PUSH
*/
void JS_PUSH_DefaultInterruptHandler(void){
    // add your JS_PUSH interrupt custom code
    // or set custom function using JS_PUSH_SetInterruptHandler()
}
   
/**
   JS_LEFT Interrupt Service Routine
*/
void JS_LEFT_ISR(void) {

    // Add custom JS_LEFT code

    // Call the interrupt handler for the callback registered at runtime
    if(JS_LEFT_InterruptHandler)
    {
        JS_LEFT_InterruptHandler();
    }
    IOCCFbits.IOCCF1 = 0;
}

/**
  Allows selecting an interrupt handler for JS_LEFT at application runtime
*/
void JS_LEFT_SetInterruptHandler(void (* InterruptHandler)(void)){
    JS_LEFT_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for JS_LEFT
*/
void JS_LEFT_DefaultInterruptHandler(void){
    // add your JS_LEFT interrupt custom code
    // or set custom function using JS_LEFT_SetInterruptHandler()
}
   
/**
   JS_UP Interrupt Service Routine
*/
void JS_UP_ISR(void) {

    // Add custom JS_UP code

    // Call the interrupt handler for the callback registered at runtime
    if(JS_UP_InterruptHandler)
    {
        JS_UP_InterruptHandler();
    }
    IOCCFbits.IOCCF2 = 0;
}

/**
  Allows selecting an interrupt handler for JS_UP at application runtime
*/
void JS_UP_SetInterruptHandler(void (* InterruptHandler)(void)){
    JS_UP_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for JS_UP
*/
void JS_UP_DefaultInterruptHandler(void){
    // add your JS_UP interrupt custom code
    // or set custom function using JS_UP_SetInterruptHandler()
}
   
/**
   JS_DOWN Interrupt Service Routine
*/
void JS_DOWN_ISR(void) {

    // Add custom JS_DOWN code

    // Call the interrupt handler for the callback registered at runtime
    if(JS_DOWN_InterruptHandler)
    {
        JS_DOWN_InterruptHandler();
    }
    IOCCFbits.IOCCF5 = 0;
}

/**
  Allows selecting an interrupt handler for JS_DOWN at application runtime
*/
void JS_DOWN_SetInterruptHandler(void (* InterruptHandler)(void)){
    JS_DOWN_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for JS_DOWN
*/
void JS_DOWN_DefaultInterruptHandler(void){
    // add your JS_DOWN interrupt custom code
    // or set custom function using JS_DOWN_SetInterruptHandler()
}
   
/**
   JS_RIGHT Interrupt Service Routine
*/
void JS_RIGHT_ISR(void) {

    // Add custom JS_RIGHT code

    // Call the interrupt handler for the callback registered at runtime
    if(JS_RIGHT_InterruptHandler)
    {
        JS_RIGHT_InterruptHandler();
    }
    IOCCFbits.IOCCF6 = 0;
}

/**
  Allows selecting an interrupt handler for JS_RIGHT at application runtime
*/
void JS_RIGHT_SetInterruptHandler(void (* InterruptHandler)(void)){
    JS_RIGHT_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for JS_RIGHT
*/
void JS_RIGHT_DefaultInterruptHandler(void){
    // add your JS_RIGHT interrupt custom code
    // or set custom function using JS_RIGHT_SetInterruptHandler()
}
/**
 End of File
*/