        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8
        EXPORT RDASM

RDASM
        push {r1-r3, lr}
        mov  r1, r0        ; r1 = puntero base temporal

        str  r0, [r1]      ; Guardar R0
        add  r1, r1, #4

        str  r1, [r1]      ; Guardar R1
        add  r1, r1, #4

        str  r2, [r1]      ; Guardar R2
        add  r1, r1, #4

        str  r3, [r1]      ; Guardar R3
        add  r1, r1, #4

        str  r4, [r1]      ; Guardar R4
        add  r1, r1, #4

        str  r5, [r1]      ; Guardar R5
        add  r1, r1, #4

        str  r6, [r1]      ; Guardar R6
        add  r1, r1, #4

        str  r7, [r1]      ; Guardar R7
        add  r1, r1, #4

        str  r8, [r1]      ; Guardar R8
        add  r1, r1, #4

        str  r9, [r1]      ; Guardar R9
        add  r1, r1, #4

        str  r10, [r1]     ; Guardar R10
        add  r1, r1, #4

        str  r11, [r1]     ; Guardar R11
        add  r1, r1, #4

        str  r12, [r1]     ; Guardar R12
        add  r1, r1, #4

        mov  r2, sp        ; Guardar SP
        str  r2, [r1]
        add  r1, r1, #4

        mov  r2, lr        ; Guardar LR
        str  r2, [r1]
        add  r1, r1, #4

        mov  r2, pc        ; Guardar PC
        str  r2, [r1]

        pop  {r1-r3, pc}

        END
