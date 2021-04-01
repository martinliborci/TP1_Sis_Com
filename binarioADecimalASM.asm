;Prueba de git pull

; int binarioADecimalASM(char *binario, unsigned int longitud) 
; convierte una cadena de caracteres de 1 y 0 a una variable entera
; Parametros:
;   binario  - String conteniendo 0s y 1s en ASCII (en [ebp + 8])
;   longitud - Longitud del string (en [ebp + 12])                     

; STACK FRAME:
; ebp + 12	longitud
; ebp +  8	binario
; ebp +  4	dirección retorno
; ebp		ebp

segment .text
        global  binarioADecimalASM
 binarioADecimalASM:
 	enter   0,0                     ; 
        
        push    ebx					; utilizado para rotar a la izquierda un 1
        push	ecx					; utilizado como contador bucle
        push    edx                                     ; utilizado para representar el string en decimal
        push    edi                                     

        ; apuntar al final del string
        mov eax, [ebp +  8]                             ; binario
        add eax, [ebp + 12]                             ; binario + longitud
        dec eax                                         ; binario + longitud -1
        mov edi, eax                                    ; edi = dirección donde termina el string
        std                                             ; posdecremento en el registro edi    

        mov eax, '1'					; al = ASCII '1'
        mov ecx, [ebp + 12]				; contador = longitud del string
        mov edx, 0					; decimal = 0
        mov ebx, 1                                      ; 1 a rotar hacia la izquierda 

bucle:
        scasb                                           ; ¿ [es:edi] == al ?
        jne noesununo
        or edx, ebx                                     ; colocar el 1 en decimal
noesununo:
        shl  ebx, 1                                     ; desplazar el 1 una posición a la izquierda
        loop bucle
       
        mov eax, edx                                    ; return decimal

        pop edi
        pop edx
        pop ecx
        pop ebx

        leave
        ret
