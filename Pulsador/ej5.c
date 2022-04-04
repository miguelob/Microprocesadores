#include<xc.h>

#define PIN_PULSADOR 5

int main(void){
    int pulsador_ant, pulsador_act;
    int i = 1; //contador para el bucle
    int valor = 0xFF;
    TRISC = ~0x0F;
    LATC = 0xFF;
    
    TRISB = 0xFF;
    
    pulsador_ant = (PORTB>>PIN_PULSADOR) & 1;
    while(1){
        pulsador_act = (PORTB>>PIN_PULSADOR) & 1;
        if((pulsador_act != pulsador_ant) && (pulsador_act == 0)){
            if(i <=15){
                valor = ~(i);
            }else{
                valor = 0x0F;
                i = 0;
            }
            i++;
        }
        pulsador_ant = pulsador_act;
        LATC = valor;
    }
}