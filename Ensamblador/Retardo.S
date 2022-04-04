#include <xc.h> // Define los registros de los periféricos

	.text # sección de código

	 # Se define el nombre de la función como global para poder llamarla desde C
	.global Retardo
	.ent Retardo # Introduce el símbolo NOMBRE_FUNCION en el código para depuración

Retardo:
	
	#ponemos inicialmente a 0 los registros T2CON, TMR2 e IFS0 (nivel registro).
	la t4,T2CON
	sw zero,0(t4)
	
	la t0,TMR2
	sw zero,0(t0)
	
	la t2, IFS0
	sw zero,0(t2)
	
	#ponemos el registro PR2 con el valor del retardo que queremos (1 ms)
	la t0, PR2
	ori t1, zero, 4999
	sw  t1,0(t0)
	
	#encendemos el timer (T2CON a 1)
	ori t0, zero, 0x8000
	sw t0 ,0(t4)
	
	#bucle para repetir el retardo de 1 ms a0 
	beq a0, zero, Fin #salir de la función si el retardo que recibimos como parámetro =0.
	add t1,zero,zero #puesta a 0 del contador
Bucle:  slt t3, t1, a0 #comprobamos que el contador es menor que a0 
	beq t3,zero,Fin  #de lo contrario salimmos del bucle
W8:	lw t0, 0(t2) #leemos IFS0
	andi t9, t0, 0x200 #sacamos el valor de IFS0.T2IF
	beq t9,zero, W8 #saltamos a W8 mientras dicho valor sea 0
	
	sw zero, 0(t2) #ponemos a 0 IFS0
	addi t1,t1,1 #incrementamos contador +1
	beq zero,zero,Bucle #sigue en el bucle
	
	sw zero,0(t4) #ponemos a 0 T2CON 
	
Fin: jr ra #volvemos al main

	.end Retardo # Indica el final de la función (para depuración)
	
	
