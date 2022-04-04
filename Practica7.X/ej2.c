#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"
#include "UART1.h"

#define PIN_PULSADOR 5

int main(int argc, char** argv) {
    char c;
    InicializarUART1(9600);
    INTCONbits.MVEC = 1;
    asm(" ei");
    
    while(1){
        c = getcUART ();
        if(c != '\0'){
            putcUART (c);
        }
    }
    return (EXIT_SUCCESS);
}

