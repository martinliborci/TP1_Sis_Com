; void PRE_CDECL resta( int n, int m, int * resp) POST_CDECL;
; resta 2 enteros
; Parametros:
;   n    - 1° operando de la resta (en [ebp + 8])
;   m    - 2° operando de la resta (en [ebp + 12])                     
;   resp - puntero al resultado de la resta (en [ebp + 16])

; STACK FRAME:
; ebp + 16      res
; ebp + 12      m
; ebp +  8      n
; ebp +  4      dir retorno
; ebp           ebp
; ebp -  4      resp

segment .text
        global  resta
;
; variable local:
;   res (en [ebp-4])
resta:
        enter   4,0                     ;alocar espacio en el stack para la variable local
        push    ebx               

        mov     dword [ebp - 4],0       ;res = 0

        mov     eax, [ebp + 8]          ;eax = 1° operando
        sub     eax, [ebp + 12]         ;eax = eax - 2° operando   

        mov     ebx, [ebp + 16]         ;ebx = direccion resp
        mov     [ebx], eax              ;res = eax

        pop     ebx                     ;restore ebx
        leave
        ret