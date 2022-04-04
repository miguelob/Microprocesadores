#include <xc.h>
#include <stdint.h>
#include "temporizador3.h"

void inicializaReloj3(void){
    T3CON = 0;
    TMR3 = 0;
    PR3 = 39061;
    IPC3bits.T3IP = 4;
    IPC3bits.T3IS = 0;
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
    T3CON = 0x8060;
}
void __attribute__(( vector ( _TIMER_3_VECTOR ) , interrupt ( IPL4SOFT ) , nomips16 ) )
    InterrupcionTimer3 ( void ){
    IFS0bits.T3IF = 0;
    LATC  ^=  1 << 2;
}
