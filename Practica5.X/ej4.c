#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Pic32Ini.h"
#include "temporizador2.h"

#define MAX_PULSACIONES 3
#define TIME_RESET 4
# define PIN_PULSADOR 5

int main ( void ){
    int pulsador_ant, pulsador_act;
    int i = 0;
    ANSELC &= ~0xF;
    
    inicializaReloj2();
    
    TRISC = 0xF4;
    LATC = 0xFF;
    TRISB = 0xFF;
    
    INTCONbits.MVEC = 1;
    asm(" ei");
     
    pulsador_ant = (PORTB>>PIN_PULSADOR) & 1;
    while (1) {
        // Se lee el estado del pulsador
        pulsador_act = (PORTB>>PIN_PULSADOR) & 1;
        if((pulsador_act != pulsador_ant) && (pulsador_act == 0)){
            contMas1();
        }
       /* if(getContador()>=MAX_PULSACIONES){
            encender();
        }*/
        pulsador_ant = pulsador_act;
    }
 }