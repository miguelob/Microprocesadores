/* 
 * File:   Main.c
 * Author: oleob
 *
 * Created on January 26, 2020, 4:30 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
/*
 * 
 */
int main(int argc, char** argv) {
    int i = 0;
    
    TRISC &= ~0x0F;
    PORTC &= ~0x0F;
    
    while(1){
        i = i + 1;
    }
    return 0;
}

