#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

int main(int argc, char** argv) {
    TRISC = 0xF0;
    LATC = 0x0B; //Para el 3.1
    LATC = 0x03; //Para el 3.2
    
    while(1){  
    }
    return (EXIT_SUCCESS);
}

