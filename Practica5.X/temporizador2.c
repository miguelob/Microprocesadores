#include <xc.h>
#include <stdint.h>
#include "temporizador2.h"

#define MAX_PULSACIONES 5

static uint32_t contador = 0;
static uint32_t espera=0;
int i;

void inicializaReloj2(void){
    T2CON = 0;
    TMR2 = 0;
    PR2 = 19530;
    IPC2bits.T2IP = 2;
    IPC2bits.T2IS = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    T2CON = 0x8070;
}
void __attribute__ (( vector ( _TIMER_2_VECTOR ) , interrupt ( IPL2SOFT ) , nomips16 ) )
InterrupcionTimer2 ( void ){
    IFS0bits.T2IF = 0;
    asm(" di");
    LATC  ^=  1 << 3;
    asm(" ei");
    
    contador=0;
    
    if(espera > 0){
        espera--;
    
        asm("di");
        LATC &=  ~(1 << 1);
        asm("ei");
    }else{
        asm("di");
        LATC |=  1 << 1;
        asm("ei");
    }
}
/*void __attribute__ (( vector ( _TIMER_2_VECTOR ) , interrupt ( IPL2SOFT ) , nomips16 ) )
InterrupcionTimer2 ( void ){
    IFS0bits.T2IF = 0;
    LATC  ^=  1 << 3;
}*/
void contMas1(void){
    contador++;
    if(contador == MAX_PULSACIONES){
       espera = 4;
    }
    
    
}