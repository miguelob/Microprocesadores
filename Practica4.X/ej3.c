# include <xc.h>
# define PIN_PULSADOR 5

int main ( void ){
    int pulsador ;

    TRISC = 0xFE;
    LATC = 0xFF;
    TRISB = 0xFF;

    while (1) {
        // Se lee el estado del pulsador
        pulsador = ( PORTB >> PIN_PULSADOR) & 1;
        if( pulsador == 0) {
            //LATC &= 1;
            asm (" lui $v0 , 0xBF88 "); // 0xBF88 = -16504
            asm (" lw $v1 , 25136( $v0 )") ;
            asm (" addiu $a0, $zero, 0xFFFE");
            asm (" and $v1, $v1, $a0");
            asm (" sw $v1, 25136($v0)");
        } else {
            //LATC |= 1;
            asm (" lui $v0 , 0xBF88 ");
            asm (" lw $v1 , 25136( $v0 )") ;
            asm (" ori $v1, $v1, 1");
            asm (" sw $v1, 25136($v0)");
        }
    }
}
