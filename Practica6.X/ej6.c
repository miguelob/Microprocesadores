/* 
 * File:   ej6.c
 * Author: oleob
 *
 * Created on February 22, 2020, 10:47 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"

#define PIN_PULSADOR 5

/*
 * 
 */
int main(int argc, char** argv) {
    char c;

    ANSELB &= ~((1 << 7) | (1 << PIN_PULSADOR) | (1 << 13));
    ANSELC &= 0xF0;

    TRISC = 0xF0;
    LATC = 0xFF;

    TRISB |= (1 << 13);
    LATB |= (1 << 7); //transmisor stop cte y pulsador en in

    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    U1RXR = 3;
    RPB7R = 1;
    SYSKEY = 0x1CA11CA1;

    U1BRG = 32; //9600 bds


    U1STAbits.URXEN = 1;
    U1MODE = 0x8000; //8bits sin paridad

    U1STAbits.UTXEN = 0; // se habilita transmisor

    while (1) {
        if (U1STAbits.URXDA == 1) { //comprobar que llega algo con un if
            c = U1RXREG;
            LATC = ~c;
            U1STAbits.UTXEN = 1; //
            U1TXREG = c;
            while (U1STAbits.TRMT == 0);
            U1STAbits.UTXEN = 0; // 
        }
    }

    return (EXIT_SUCCESS);
}

