/* 
 * File:   Ej3.c
 * Author: oleob
 *
 * Created on April 26, 2020, 5:08 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"

#define PIN_PULSADOR 5
#define PIN_PULSADOR_2 4
#define PIN_AN1 1
#define INC_60_GRADOS 833

int main(int argc, char** argv) {
    InicializarReloj();
    
    int pulsador_ant, pulsador_act, pulsador_ant1, pulsador_act1;
    int t_alto = 2500;
    
    ANSELB |= 1 << PIN_PULSADOR;
    
    LATA = 0;
    LATB = 0;
    LATC = 0;
    
    TRISA = (1 << PIN_AN1);
    TRISB = (1 << PIN_PULSADOR) | (1 << PIN_PULSADOR_2);
    TRISC = 0;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB15R = 5;
    SYSKEY = 0x1CA11CA1;
    
    OC1CON = 0;
    OC1R = 2500;
    OC1RS = 2500;
    OC1CON = 0x8006;
    
    T2CON = 0;
    TMR2 = 0;
    PR2 = 49999;
    T2CON = 0x8010;
    
    pulsador_ant = (PORTB >> PIN_PULSADOR) & 1;
    pulsador_ant1 = (PORTB >> PIN_PULSADOR_2) & 1;
    
    while (1){
        pulsador_act = (PORTB >> PIN_PULSADOR) & 1;
        pulsador_act1 = (PORTB >> PIN_PULSADOR_2) & 1;
        if((pulsador_act != pulsador_ant) && (pulsador_act == 0)){
            t_alto += INC_60_GRADOS;
            if(t_alto > 5000){
                t_alto = 2500;
            }
            OC1RS = t_alto ;
            OC1CON = 0;
            OC1R = t_alto ;
            OC1CON = 0x8006;
        }
        if((pulsador_act1 != pulsador_ant1) && (pulsador_act1 == 0)){
            t_alto -= INC_60_GRADOS;
            if(t_alto < 2500){
                t_alto = 5000;
            }
            OC1RS = t_alto ;
            OC1CON = 0;
            OC1R = t_alto ;
            OC1CON = 0x8006;
        }
        pulsador_ant = pulsador_act;
        pulsador_ant1 = pulsador_act1;
    }
    
    return (EXIT_SUCCESS);
}

