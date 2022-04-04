/* 
 * File:   Ej3.c
 * Author: oleob
 *
 * Created on April 20, 2020, 10:24 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"

#define CONTROL 15

int temperatura;

int main(int argc, char** argv) {
    int consigna, temp;
    
    InicializarReloj();
    
    ANSELC &= ~0x3FF;
    ANSELB = ~(1<<CONTROL);
    
    TRISA = 1 << 1;
    TRISB = 1 << 3;
    TRISC = 0x3F0; 
    
    LATA = 0;
    LATB = 0;
    LATC = 0x0F;
    
    AD1CON1 = 0;
    AD1CON2 = 3 << 2;
    AD1CON3 = 0x0200;
    
    AD1CHS = 0x00050000;
    AD1CON1bits.SSRC = 2;
    AD1CON1bits.ASAM = 1;
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;
    IPC5bits.AD1IP = 2;
    IPC5bits.AD1IS = 0;
    AD1CON1bits.ON = 1;
    
    T3CON = 0;
    TMR3 = 0;
    PR3 = 12499;
    T3CON = 0x8000;
    
    INTCONbits.MVEC = 1;
    asm("ei");
    
    while(1){
        consigna = (PORTC & 0x3F0)>>4;
        asm("di");
        temp = temperatura;
        asm("ei");
        if((temp +1) > consigna){
            LATB &= ~(1 << CONTROL);
        }else if((temp -1) < consigna){
            LATB |= (1 << CONTROL);
        }
    }
    
    return (EXIT_SUCCESS);
}
__attribute__((vector(23), interrupt(IPL2SOFT),nomips16))
void interrupcionADC(void){
    IFS0bits.AD1IF = 0;
    int valor_medio;
    
    valor_medio = (ADC1BUF0+ADC1BUF1+ADC1BUF2+ADC1BUF3)>>2;
    
    temperatura = valor_medio>>4;
    
}

