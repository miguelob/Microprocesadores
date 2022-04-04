#include <xc.h>
#include "UART1.h"

#define TAM_COLA 100

//Para utilizar colas, definimos los datos en una estructura
typedef struct{
    int icabeza;
    int icola;
    char cola[TAM_COLA];
} COLA_T;

static COLA_T cola_rx; //cola para el receptor
static COLA_T cola_tx; //cola para el transmisor

/**
* Inicialización de la UART1 con un bps dado.
*
* @param [in] int baudios -> Baudios con los que hay que configurar la UART.
* @param [out ] void.
* @return void. Solo configura la UART.
*/
void InicializarUART1(int baudios){
    
    if(baudios > 38400){
        U1BRG = ((5*1000000)/(4*baudios)) -1;
        U1MODEbits.BRGH = 0;
    }else{
        U1BRG = ((5*1000000)/(16*baudios)) -1;
        U1MODEbits.BRGH = 1;
    }
    // Activamos las interrupciones del receptor.
    IFS1bits.U1RXIF = 0; // Borro flag por si acaso
    IEC1bits.U1RXIE = 1; // Habilito interrupciones
    IFS1bits.U1TXIF = 0; // Borro flag del transmisor por si acaso
    IPC8bits.U1IP = 3; // Prioridad 3
    IPC8bits.U1IS = 1; // Subprioridad 1
    
    // Conectamos U1RX y U1TX a los pines RB13 y RB7 del micro
    ANSELB &= ~((1<<13)|(1<<7)); // Pines digitales
    TRISB |= 1<<13; // Y RB13 como entrada
    LATB |= 1<<7; // A 1 si el transmisor está inhabilitado.
    SYSKEY=0xAA996655; // Se desbloquean los registros
    SYSKEY=0x556699AA; // de configuración.
    U1RXR = 3; // U1RX conectado a RB13.
    RPB7R = 1; // U1TX conectado a RB7.
    SYSKEY=0x1CA11CA1; // Se vuelven a bloquear.
    U1STAbits.URXISEL = 0; // Interrupción cuando llegue 1 char.
    U1STAbits.UTXISEL = 2; // Interrupción cuando FIFO vacía.
    U1STAbits.URXEN = 1; // Se habilita el receptor.
    U1STAbits.UTXEN = 1; // Y el transmisor
    U1MODE = 0x8000; // Se arranca la UART
    
}

//interrupción UART1. Se mira si ha interrumpido el receptor o el transmisor
//y si se puede, se lee o se escribe en la cola.
__attribute__((vector(32), interrupt(IPL3SOFT),nomips16))
void InterrupcionUART1(void){
    if(IFS1bits.U1RXIF == 1){ // Ha interrumpido el receptor
        if( (cola_rx.icabeza+1 == cola_rx.icola) || (cola_rx.icabeza +1 == TAM_COLA && cola_rx.icola == 0)){
        // La cola está llena
        }else{
            cola_rx.cola[cola_rx.icabeza] = U1RXREG; // Lee carácter de la UART
            cola_rx.icabeza ++;
            if(cola_rx.icabeza == TAM_COLA){
                cola_rx.icabeza = 0;
            }
        }
        IFS1bits.U1RXIF = 0; // Y para terminar se borra el flag
    }
    
    if(IFS1bits.U1TXIF == 1){ // Ha interrumpido el transmisor
         // Se extrae un carácter de la cola y se envía
        if(cola_tx.icola != cola_tx.icabeza){ // Hay datos nuevos
        U1TXREG = cola_tx.cola[cola_tx.icola];
        cola_tx.icola ++;
        
        if(cola_tx.icola == TAM_COLA){
            cola_tx.icola = 0;
        }
        
        }else{ // Se ha vaciado la cola.
            IEC1bits.U1TXIE = 0; // Para evitar bucle sin fin
        }
        
        IFS1bits.U1TXIF = 0; // Y para terminar se borra el flag
    }
}

/**
* Función que nos permite escribir un caracter en la cola para poder enviarlo.
*
* @param [in] char c -> Caracter a enviar por la UART. La funcion lo añade a la
 * cola de transmisión.
* @param [out ] void.
* @return void.
*/
void putcUART(char c){
    if( (cola_tx.icabeza+1 == cola_tx.icola) || (cola_tx.icabeza+1 == TAM_COLA && cola_tx.icola == 0)){
        // La cola está llena. Se aborta el envío de
        // los caracteres que restan
    }else{
        cola_tx.cola[cola_tx.icabeza] = c; // Copia el carácter en la cola
        cola_tx.icabeza ++;

        if(cola_tx.icabeza == TAM_COLA){
            cola_tx.icabeza = 0;
        }
    }
    // Se habilitan las interrupciones del transmisor para
    // comenzar a enviar
    IEC1bits.U1TXIE = 1;
}

/**
* Función que nos permite escribir una string en la cola para poder enviarla.
*
* @param [in] char *ps -> Recibe el Array de chars, que a la función llega el
 * puntero del primer caracter. La funcion añade los caracteres a la cola del
 * transmisor.
* @param [out ] void.
* @return void.
*/
void putsUART(char *ps){
    while(*ps != '\0'){
        if( (cola_tx.icabeza+1 == cola_tx.icola) || (cola_tx.icabeza+1 == TAM_COLA && cola_tx.icola == 0)){
            // La cola está llena. Se aborta el envío de
            // los caracteres que restan
            break;
        }else{
            cola_tx.cola[cola_tx.icabeza] = *ps; // Copia el carácter en la cola
            ps++; // Apunto al siguiente carácter de la cadena
            cola_tx.icabeza ++;

            if(cola_tx.icabeza == TAM_COLA){
                cola_tx.icabeza = 0;
            }
        }
    }
    // Se habilitan las interrupciones del transmisor para
    // comenzar a enviar
    IEC1bits.U1TXIE = 1;
}

/**
* Función para leer un caracter de la UART.
*
* @param [in] void.
* @param [out ] char.
* @return devuelve el siguiente caracter a leer disponible en la cola.
*/
char getcUART(void){
    char c;
    if(cola_rx.icola != cola_rx.icabeza){ // Hay datos nuevos
        c = cola_rx.cola[cola_rx.icola];
        cola_rx.icola ++;
        if(cola_rx.icola == TAM_COLA){
        cola_rx.icola =0;
    }
    }else{ // no ha llegado nada
        c = '\0';
    }
    return c;
}