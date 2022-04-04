#include <xc.h>
#include "retardo.h"

    /**
    * Esta funcion genera un retardo del tiempo especificado.
    *
    * @param [in] retardo_ms.
    * @param [out ] int.
    * @return Se devuelve 1 si el retardo pedido es de 0 segundos, o si es demasiado
    * grande. De lo contrario se genera el retardo especificado y se devuelve 0.
    */

    int Retardo(uint16_t retardo_ms){
        int retorno = 1;
        <int divisor[8] = {1,2,4,8,16,32,64,256};
        uint64_t calculo;
        int i;
        
        T2CON = 0;
        TMR2 = 0;
        IFS0bits.T2IF = 0;
        PR2 = 0;
        
        if(retardo_ms){
            for(i=0;i<=7;i++){
                calculo = ((retardo_ms*1000000)/(divisor[i]*200)) - 1;
                if(calculo <= (uint32_t)65535){                        
                    PR2 = (uint16_t)calculo;
                    T2CON = 0x8000 | i<<4;
                    i = 8;
                    retorno = 0;
                    
                    while(IFS0bits.T2IF == 0);
                    IFS0bits.T2IF = 0;
                }
            }
        }
        return retorno;
    }
