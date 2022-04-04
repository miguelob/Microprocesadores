/* 
 * File:   Ej2.c
 * Author: oleob
 *
 * Created on April 20, 2020, 9:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"

#define PIN_POT 3
#define PIN_AN1 1

int main(int argc, char** argv) {
    
    InicializarReloj();
    
    int valor_leds;
    
    ANSELC &= ~0xF;
    
    TRISA = (1 << PIN_AN1);
    TRISB = (1 << PIN_POT);
    TRISC = 0;
    
    LATA = 0;
    LATB = 0;
    LATC = 0xF;
    
    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0x0200;
    
    AD1CHS = 0x00050000;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.ON = 1;
    
    while(1){
        AD1CON1bits.SAMP = 1;
        while(AD1CON1bits.DONE==0);
        
        valor_leds = (ADC1BUF0>>6);
        LATCCLR = ( valor_leds) & 0x0F;
        LATCSET = (~valor_leds) & 0x0F;
    }
    
    return (EXIT_SUCCESS);
}

