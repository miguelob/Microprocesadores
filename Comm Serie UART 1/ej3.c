/* 
 * File:   ej3.c
 * Author: oleob
 *
 * Created on February 22, 2020, 10:47 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"

/*
 * 
 */
int main(int argc, char** argv) {
    char c;
    ANSELB &= ~(1 << 13);
    ANSELC &= 0xF0;
    TRISC = 0xF0;
    LATC = 0xFF;
    
    TRISB |= 1 << 13;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    U1RXR = 3;
    SYSKEY = 0x1CA11CA1;
    
    U1BRG = 32; //9600 bds
    
    U1STAbits.URXEN = 1;
    U1MODE = 0x8000; //8bits sin paridad
    
    while(1){
        while(U1STAbits.URXDA == 0);
        c = U1RXREG;
        LATC = ~c;
    }
    
    return (EXIT_SUCCESS);
}
