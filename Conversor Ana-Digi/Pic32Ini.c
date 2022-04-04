#include <xc.h>
#include "Pic32Ini.h"

// Configuration bits: selected in the GUI (MCC)

// DEVCFG3
#pragma config PMDL1WAY = ON    // Peripheral Module Disable Configuration->Allow only one reconfiguration
#pragma config IOL1WAY = ON    // Peripheral Pin Select Configuration->Allow only one reconfiguration
#pragma config FUSBIDIO = ON    // USB USID Selection->Controlled by the USB Module
#pragma config FVBUSONIO = ON    // USB VBUS ON Selection->Controlled by USB Module

// DEVCFG2
#pragma config FPLLIDIV = DIV_2    // PLL Input Divider->2x Divider
#pragma config FPLLMUL = MUL_20    // PLL Multiplier->20x Multiplier
#pragma config UPLLIDIV = DIV_12    // USB PLL Input Divider->12x Divider
#pragma config UPLLEN = OFF    // USB PLL Enable->Disabled and Bypassed
#pragma config FPLLODIV = DIV_2    // System PLL Output Clock Divider->PLL Divide by 2

// DEVCFG1
#pragma config FNOSC = PRIPLL    // Oscillator Selection Bits->Primary Osc w/PLL (XT+,HS+,EC+PLL)
#pragma config FSOSCEN = OFF    // Secondary Oscillator Enable->Disabled
#pragma config IESO = ON    // Internal/External Switch Over->Enabled
#pragma config POSCMOD = XT    // Primary Oscillator Configuration->XT osc mode
#pragma config OSCIOFNC = OFF    // CLKO Output Signal Active on the OSCO Pin->Disabled
#pragma config FPBDIV = DIV_8    // Peripheral Clock Divisor->Pb_Clk is Sys_Clk/8
#pragma config FCKSM = CSDCMD    // Clock Switching and Monitor Selection->Clock Switch Disable, FSCM Disabled
#pragma config WDTPS = PS1048576    // Watchdog Timer Postscaler->1:1048576
#pragma config WINDIS = OFF    // Watchdog Timer Window Enable->Watchdog Timer is in Non-Window Mode
#pragma config FWDTEN = OFF    // Watchdog Timer Enable->WDT Disabled (SWDTEN Bit Controls)
#pragma config FWDTWINSZ = WINSZ_25    // Watchdog Timer Window Size->Window Size is 25%

// DEVCFG0
#pragma config DEBUG = OFF    // Background Debugger Enable->Debugger is Disabled
#pragma config JTAGEN = ON    // JTAG Enable->JTAG Port Enabled
#pragma config ICESEL = ICS_PGx1    // ICE/ICD Comm Channel Select->Communicate on PGEC1/PGED1
#pragma config PWP = OFF    // Program Flash Write Protect->Disable
#pragma config BWP = OFF    // Boot Flash Write Protect bit->Protection Disabled
#pragma config CP = OFF    // Code Protect->Protection Disabled


void InicializarReloj(void)
{
    SYSKEY = 0x0;         // Nos aseguramos que OSCCON está bloqueado
    SYSKEY = 0xAA996655;  // Se escribe la primera clave en SYSKEY
    SYSKEY = 0x556699AA;  // Se escribe la segunda clave en SYSKEY
    //  Ahora OSCCON está desbloqueado y podemos modificarlo
    
    // Se configura el reloj para usar el oscilador externo usando PLL.
    // El oscilador está dividido entre 2, pues el PLL ha de tener una entrada
    // entre 4 y 5 MHz (DEVCFG3.FPLLIDIV = 001).
    // Al PLL entran por tanto 8MHz/2 = 4 MHz, luego el PLL lo
    // Multiplica por 20 (80 MHz) y esta salida se divide entre 2 para 
    // obtener un reloj principal a 40 MHz. Este reloj se divide por 8 para
    // obtener el reloj del bus de periféricos. Para ello, en el
    // registro OSCCON se hace:
    // PLLODIV = 001 (div. por 2)
    // PBDIV = 11 (div. por 8)
    // PLLMULT = 101 (mult. por 20)
    // COSC = 011 (Oscilador principal con PLL)
    // NOSC = 011 (Oscilador principal con PLL)
    OSCCON = 0x081D3300;

    // Una vez hemos terminado, lo volvemos a bloquear
    SYSKEY = 0x0;
}
