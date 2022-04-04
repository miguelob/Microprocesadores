/* 
 * File:   ej4.c
 * Author: oleob
 *
 * Created on February 22, 2020, 10:47 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"

#define TAM_CAD 20
# define PIN_PULSADOR 5

/*
 * 
 */
int main(int argc, char** argv) {
    int pulsador_ant, pulsador_act;
    char cad_tx[TAM_CAD] = "Hola mundo.\n";
    int i_cad_tx = 0;
    ANSELB &= ~((1 << 7) | (1 <<PIN_PULSADOR));
    
    LATB |= (1<<7); //transmisor stop cte y pulsador en in
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB7R = 1;
    SYSKEY = 0x1CA11CA1;
    
    U1BRG = 32; //9600 bds
    
    U1STAbits.UTXEN = 0; // se inhabilita transmisor
    U1MODE = 0x8000; //8bits sin paridad
    
    pulsador_ant = (PORTB>>PIN_PULSADOR) & 1;
    while(1){
         pulsador_act = (PORTB>>PIN_PULSADOR) & 1;
        if((pulsador_act != pulsador_ant) && (pulsador_act == 0)){
            U1STAbits.UTXEN = 1; //
            while(cad_tx[i_cad_tx] != '\0'){
                U1TXREG = cad_tx[i_cad_tx];
                while(U1STAbits.TRMT == 0);
                i_cad_tx++;
            }
        }
         pulsador_ant = pulsador_act;
         i_cad_tx = 0;
         U1STAbits.UTXEN = 0; 
    }
    
    return (EXIT_SUCCESS);
}

