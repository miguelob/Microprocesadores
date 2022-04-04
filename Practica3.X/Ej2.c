/* 
 * File:   Ej2.c
 * Author: oleob
 *
 * Created on February 1, 2020, 10:54 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"

#define PIN_LED 0

/*
 * 
 */
int main(int argc, char** argv) {
    TRISC = 0;
    LATC = 0x0F; //Empieza apagado
    
    T2CON = 0;
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    PR2 = 39061; //espera 500ms
    T2CON = 0x8060; //Prescaler a 64
    
    while(1){
        while(IFS0bits.T2IF == 0); //esperamos al final de la cuenta
        IFS0bits.T2IF = 0;
        LATC ^= 1<<PIN_LED; //invertimos el led
    }
    return (EXIT_SUCCESS);
}

