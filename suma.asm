; void PRE_CDECL suma( int n, int m, int * sump) POST_CDECL
; suma 2 enteros
; Parametros:
;   n    - 1° operando de la suma (en [ebp + 8])
;   m    - 2° operando de la suma (en [ebp + 12])                     
;   sump - puntero al resultado de la suma (en [ebp + 16])

; STACK FRAME:
; ebp + 16      resp
; ebp + 12      m
; ebp +  8      n
; ebp +  4      dir retorno
; ebp           ebp
; ebp -  4      sum

segment .text
        global  suma
;
; variable local:
;   sum (en [ebp-4])
suma:
        enter   4,0                     ; alocar espacio en el stack para la variable local
        push    ebx               

        mov     dword [ebp - 4],0       ; sum = 0

        mov     eax, [ebp + 8]          ;eax = 1° operando (n)
        add     eax, [ebp + 12]         ;eax = eax + 2° operando (m)

        mov     ebx, [ebp + 16]         ;ebx = dirección sump
        mov     [ebx], eax              ;sump = eax

        pop     ebx                     ; restore ebx
        leave
        ret
