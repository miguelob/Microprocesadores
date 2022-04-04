#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define PIN_PULSADOR 5

int main(int argc, char** argv) {
    int pulsador;
    
    TRISC = 0xF0;
    LATC = 0xFF;
    TRISB = 0xFF;
    
    while(1){
        pulsador = (PORTB >> PIN_PULSADOR) & 1; //Se lee el estado del pulsador
        if(pulsador == 0){ //Si se pulsa el boton (pulsador = 0)
            LATC &= ~1; //Pone el led0 a 0 (Se enciende)
        }else{ //Si no estan pulsados
            LATC |= 1; //Pone el led0 a 1 (Se apaga)
        }
    }
    return (EXIT_SUCCESS);
}

