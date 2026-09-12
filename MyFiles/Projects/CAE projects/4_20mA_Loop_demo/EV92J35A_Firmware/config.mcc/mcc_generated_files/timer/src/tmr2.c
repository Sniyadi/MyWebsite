/**
 * TMR2 Generated Timer Driver File
 *
 * @file tmr2.c
 * 
 * @ingroup  timerdriver
 * 
 * @brief Driver implementation for the TMR2 Timer driver.
 *
 * @version Driver Version 4.0.2
 *
 * @version Package Version 5.1.3
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../tmr2.h"

const struct TIMER_INTERFACE Timer2 = {
    .Initialize = TMR2_Initialize,
    .Deinitialize = TMR2_Deinitialize,
    .Start = TMR2_Start,
    .Stop = TMR2_Stop,
    .PeriodSet = TMR2_PeriodSet,
    .PeriodGet = TMR2_PeriodGet,
    .CounterGet = TMR2_CounterGet,
    .CounterSet = TMR2_CounterSet,
    .MaxCountGet = TMR2_MaxCountGet,
    .TimeoutCallbackRegister = TMR2_PeriodMatchCallbackRegister,
    .Tasks = NULL
};

static void (*TMR2_PeriodMatchCallback)(void);
static void TMR2_DefaultPeriodMatchCallback(void);

/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void)
{
    T2CLKCON = (uint8_t)((1 << _T2CLKCON_T2CS_POSN));  // T2CS FOSC/4

    T2HLT = (uint8_t)((0 << _T2HLT_T2MODE_POSN)   // T2MODE Software control
        | (0 << _T2HLT_T2CKSYNC_POSN)   // T2CKSYNC Not Synchronized
        | (0 << _T2HLT_T2CKPOL_POSN)   // T2CKPOL Rising Edge
        | (0 << _T2HLT_T2PSYNC_POSN));  // T2PSYNC Not Synchronized

    T2RST = (uint8_t)((0 << _T2RST_T2RSEL_POSN));  // T2RSEL T2CKIPPS pin

    T2PR = (uint8_t)0xEA;            // Period 0.03008s; Timer Prescaled Frequency 7812Hz; Count 234

    T2TMR = (uint8_t)0x0;

    TMR2_PeriodMatchCallback = TMR2_DefaultPeriodMatchCallback;
    
    PIR3bits.TMR2IF = 0U;   
    PIE3bits.TMR2IE = 1U;

    T2CON = (uint8_t)((5 << _T2CON_T2CKPS_POSN)   // T2CKPS 1:32
        | (1 << _T2CON_TMR2ON_POSN)   // TMR2ON on
        | (0 << _T2CON_T2OUTPS_POSN));  // T2OUTPS 1:1
}

void TMR2_Deinitialize(void)
{
    T2CONbits.TMR2ON = 0U;
    
    PIR3bits.TMR2IF = 0U;	   
    PIE3bits.TMR2IE = 0U;		
    
    T2CON = (uint8_t)0x0;
    T2CLKCON = (uint8_t)0x0;
    T2HLT = (uint8_t)0x0;
    T2RST = (uint8_t)0x0;
    T2PR = (uint8_t)0xFF;
    T2TMR = (uint8_t)0x0;
}

void TMR2_Start(void)
{   
   T2CONbits.TMR2ON = 1U;
}

void TMR2_Stop(void)
{   
    T2CONbits.TMR2ON = 0U;
}

uint32_t TMR2_CounterGet(void)
{
    return (uint32_t)T2TMR;
}

void TMR2_CounterSet(uint32_t count)
{  
    T2TMR = (uint8_t)count;
}

void TMR2_PeriodSet(uint32_t periodVal)
{
    T2PR = (uint8_t)periodVal;
}

uint32_t TMR2_PeriodGet(void)
{
    return (uint32_t)T2PR;
}

uint32_t TMR2_MaxCountGet(void)
{
    return (uint32_t)TMR2_MAX_COUNT;
}

void TMR2_ISR(void)
{
    // The ticker is set to 1 -> The callback function gets called every time this ISR executes.
    if(NULL != TMR2_PeriodMatchCallback)
    {
        TMR2_PeriodMatchCallback();
    }
   PIR3bits.TMR2IF = 0U;
}

void TMR2_PeriodMatchCallbackRegister(void (* callbackHandler)(void))
{
   TMR2_PeriodMatchCallback = callbackHandler;
}

static void TMR2_DefaultPeriodMatchCallback(void)
{
    // Default callback function
}
