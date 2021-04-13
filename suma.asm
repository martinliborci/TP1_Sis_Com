; int PRE_CDECL suma( int n, int m) POST_CDECL
; suma 2 enteros
; Parametros:
;   n    - 1° operando de la suma (en [ebp + 8])
;   m    - 2° operando de la suma (en [ebp + 12])

; STACK FRAME:
; ebp + 12      m
; ebp +  8      n
; ebp +  4      dir retorno
; ebp           ebp

segment .text
        global  suma

suma:
        enter   0,0

        mov     eax, [ebp + 8]          ; eax = 1° operando (n)
        add     eax, [ebp + 12]         ; eax = eax + 2° operando (m)
                                        ; se retorna el valor de la suma en eax
        leave
        ret
