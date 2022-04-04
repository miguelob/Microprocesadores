#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

# define PIN_PULSADOR 5

int main ( void ){
    int pulsador ;

    TRISC = 0xFE;
    LATC = 0xFF;
    TRISB = 0xFF;

    while (1) {
        // Se lee el estado del pulsador
        pulsador = ( PORTB >> PIN_PULSADOR ) & 1;
        if( pulsador == 0) {
            LATC &= ~1;
        } else {
            LATC |= 1;
        }
    }
 }