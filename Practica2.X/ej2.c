#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

int main(int argc, char** argv) {
    TRISC = 0xF0;
    LATC = 0xF0;
    
    while(1){
    }
    return (EXIT_SUCCESS);
}

