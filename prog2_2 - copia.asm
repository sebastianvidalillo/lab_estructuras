#include "msp430x16x.h" 
#define		SPinit	0x0			// Ubicación en la RAM

main
;-------------------------------------------------------------------------------        
                ORG	0x2500				; Dirección de inicio del programa
;-------------------------------------------------------------------------------
RESET	        MOV	#SPinit,SP      	; Inicio del Stack
                MOV     #0XF, R13
                CLR     R12
                
VALOR           MOV     #0X81, 0X0(R12)
                DEC     R13
                INCD    R12 
                CMP     #0X0, R13
                JNE     VALOR
                MOV     #0X1110, R14
                CALL    #COPIA
               
                BR      #EXIT			; Reemplace toda la instrucción por RET. ¿Qué ocurre?
;-------------------------------------------------------------------------------
COPIA       
                PUSH    R14
                PUSH    R15
                PUSH    R12
                MOV     R14, R15
                DECD    R12
COP1            MOV     0X0(R12), 0X0(R15)
                DECD    R12
                INCD    R15
                CMP    #0X0, R12
                JNE     COP1
                POP     R12
                POP     R15
                POP     R14
                RET
;-------------------------------------------------------------------------------
EXIT            JMP     EXIT            ; ¿Qué realiza esta instrucción?
;------------------------------------------------------------------------------ 
; Vector de interrupción asociado a Reset 
;------------------------------------------------------------------------------ 
                ORG 0xFFFE ; MSP430 RESET Vector 
                DW RESET
                END
 
