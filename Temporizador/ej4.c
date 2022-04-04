/* 
 * File:   Ej4.c
 * Author: oleob
 *
 * Created on February 1, 2020, 10:54 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "retardo.h"
#include "Pic32Ini.h"

#define PIN_LED 0

/*
 * 
 */
int main(int argc, char** argv) {
    TRISC = 0;
    LATC = 0x0F; //Empieza apagado
    
    while(1){
        if(!Retardo(500)){
            LATC ^= 1<<PIN_LED;
        }else{
            printf("\nAsegurese que el numero es distinto de 0 y no demasiado grande");
        }
    }
    return (EXIT_SUCCESS);
}

