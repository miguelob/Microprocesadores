#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xc.h>
#include "Pic32Ini.h"
#include "UART1.h"

#define TAM_CAD 10

int asciiConverter(char c);
void checkCMD(void);

static char temp[TAM_CAD];

int main(int argc, char** argv) {
    int i = 0;
    char c;
    
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    LATA = 0;
    LATB = 0;
    LATC = 0;
    
    InicializarUART1(9600);
    INTCONbits.MVEC = 1;
    asm("ei");
    
    while(1){
        c = getcUART();
        if(c != '\0'){
            temp[i] = c;
            i++;
            
            if(c == '\n'){
                i=0;
                checkCMD();
            }
        }
            
    }
    return (EXIT_SUCCESS);
}

int asciiConverter(char c){
    int retorno = 9999; // pongo este número como código de error
    if(c >= 65 && c <= 68){//letra a int;
        retorno = c-65+10;
    }else if(c >= 48 && c <= 57){//numero a int
        retorno = c-0x30;
    }
    return retorno;
}
void checkCMD(void){
    int valor = 0;
    char retorno[20];
    
    strcpy(retorno,"ERROR\n");
        switch(temp[1]){
            case 'D':
                valor = asciiConverter(temp[5]);
                if(valor != 9999){
                    switch(temp[3]){
                        case 'A':
                            if(temp[7] == '0'){
                                strcpy(retorno,"OK\n");
                                TRISA &= ~(1 << valor);
                            }else if(temp[7] == '1'){
                                strcpy(retorno,"OK\n");
                                TRISA |= (1 << valor);
                            }
                        break;
                        case 'B':
                            if(temp[7] == '0'){
                                strcpy(retorno,"OK\n");
                                TRISB &= ~(1 << valor);
                            }else if(temp[7] == '1'){
                                strcpy(retorno,"OK\n");
                                TRISB |= (1 << valor);
                            }
                        break;
                        case 'C':
                            if(temp[7] == '0'){
                                strcpy(retorno,"OK\n");
                                TRISC &= ~(1 << valor);
                            }else if(temp[7] == '1'){
                                strcpy(retorno,"OK\n");
                                TRISC |= (1 << valor);
                            }
                        break;

                    }
                }
            break;
            case 'I':
                valor = asciiConverter(temp[5]);
                if(valor != 9999){
                    switch(temp[3]){
                        case 'A':
                            if(LATA & (1 << valor)){
                                valor = 1;
                            }else{
                                valor = 0;
                            }
                            sprintf(retorno,"PI,%d\n",valor);
                        break;
                        case 'B':
                            if(LATB & (1 << valor)){
                                valor = 1;
                            }else{
                                valor = 0;
                            }
                            sprintf(retorno,"PI,%d\n",valor);
                        break;
                        case 'C':
                            if(LATC & (1 << valor)){
                                valor = 1;
                            }else{
                                valor = 0;
                            }
                            sprintf(retorno,"PI,%d\n",valor);
                        break;
                    }
                }
            break;
            case 'O':
                valor = asciiConverter(temp[5]);
                if(valor != 9999){
                     switch(temp[3]){
                        case 'A':
                            if(temp[7] == '0'){
                                strcpy(retorno,"OK\n");
                                LATA &= ~(1 << valor);
                            }else if(temp[7] == '1'){
                                strcpy(retorno,"OK\n");
                                LATA |= (1 << valor);
                            }
                        break;
                        case 'B':
                            if(temp[7] == '0'){
                                strcpy(retorno,"OK\n");
                                LATB &= ~(1 << valor);
                            }else if(temp[7] == '1'){
                                strcpy(retorno,"OK\n");
                                LATB |= (1 << valor);
                            }
                        break;
                        case 'C':
                            if(temp[7] == '0'){
                                strcpy(retorno,"OK\n");
                                LATC &= ~(1 << valor);
                            }else if(temp[7] == '1'){
                                strcpy(retorno,"OK\n");
                                LATC |= (1 << valor);
                            }
                        break;

                    }
                }
            break;
        }
        putsUART(retorno);
}

