#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "retardo.h"
#include "Pic32Ini.h"

#define PIN_LED 0

int main(int argc, char** argv) {
    TRISC = 0;
    LATC = 0x0F; //Empieza apagado
    int tiempo = 20;
    int s = 0;
    
    while(1){
        LATC = 0x0F;
        Retardo(tiempo);
        LATC = 0x0E;
        Retardo(20-tiempo);
        tiempo += s;
        if(tiempo >= 20){
            s = -1;
        }else if(tiempo <= 0){
            s = +1;
        }
    }
    return (EXIT_SUCCESS);
}

