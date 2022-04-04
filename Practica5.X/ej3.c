#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Pic32Ini.h"
#include "temporizador2.h"
#include "temporizador3.h"


# define PIN_PULSADOR 5

int main ( void ){
    int pulsador ;
    ANSELC &= ~0xF;

    inicializaReloj2();
    inicializaReloj3();
    
    TRISC = 0xF2;
    LATC = 0xFF;
    TRISB = 0xFF;
     
    INTCONbits.MVEC = 1;
    asm(" ei");
    
    while (1) {
        // Se lee el estado del pulsador
        pulsador = ( PORTB >> PIN_PULSADOR ) & 1;
        if( pulsador == 0) {
            asm(" di");
            LATC &= ~1;
            asm(" ei");
        } else {
            asm(" di");
            LATC |= 1;
            asm(" ei");
        }
    }
 }