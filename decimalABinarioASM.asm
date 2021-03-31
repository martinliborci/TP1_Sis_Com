; har * decimalABinarioASM(int decimal, char *binario, unsigned int longitud)
; convierte una cadena de caracteres de 1 y 0 a una variable entera
; Parametros:
;   decimal  - Entero que representa el valor en decimal del string 
;   binario  - String conteniendo 0s y 1s en ASCII (en [ebp + 8])
;   longitud - Longitud del string (en [ebp + 12])                     

; STACK FRAME:
; ebp + 16	longitud
; ebp + 12	binario
; ebp +  8      decimal
; ebp +  4	dirección retorno
; ebp		ebp

segment .text
        global  decimalABinarioASM
decimalABinarioASM:
 	enter   0,0                                     ; sin variables locales
        
        push    ebx					; utilizado para rotar a la derecha un 1
        push    edi                                     ; utilizado para recorrer el string binario

        ; ¿el decimal es cero?
        cmp [ebp + 8], dword 0                          ; ¿decimal == 0?
        jnz inicializarSaltarUnos                       ; si no es cero saltar
        mov edi, [ebp + 12]                             
        mov [edi], byte '0'
        inc edi
        mov [edi], byte 0
        jmp return

inicializarSaltarUnos:                                  ;saltar los ceros de la izquierda
        mov ebx,80000000h                               ; 1 << 31
saltarUnos:
        shr ebx,1                                       ; rotar ebx una posición a la derecha
        test [ebp + 8], ebx                             ; decimal & ebx, el resultado se descarta
        jz saltarUnos                                   ; si es un cero, los sigo saltando
 
        ; inicializo para recorrer edi
        cld                                             ; posincremento en edi
        mov edi, [ebp + 12]                             ; edi = binario
 bucle:       
        mov [edi], byte '1'                             ; siempre almaceno el caracter '1'
        test [ebp + 8], ebx                             ; decimal & ebx, el resultado se descarta
        jnz noEsCero                                    ; si no es cero, dejo el uno
        mov [edi], byte '0'                             ; sino lo cambio por un cero
noEsCero:
        inc edi                                         ; siguiente posición en binario
        shr ebx,1                                       ; rotar el 1 una posición a la derecha
        jnz bucle                                       ; si ebx no es cero salto, (todavía no terminé de recorrer el decimal)
        mov [edi], byte 0                               ; colacar señalizador de fin de cadena


return:
        mov eax, [ebp + 12]                              ; return binario

        pop edi
        pop ebx

        leave
        ret