#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Retardo.h"
#include "Pic32Ini.h"

#define PIN_LED 0

/*
 * 
 */
int main(int argc, char** argv) {
    TRISC = 0;
    LATC = 0x0F; //Empieza apagado
    
    while(1){
        Retardo(500);
        LATC ^= 1<<PIN_LED;
    }
    return (EXIT_SUCCESS);
}