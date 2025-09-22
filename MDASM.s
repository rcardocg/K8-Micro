		AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8
			
        EXPORT	MDASM
MDASM
		push {r3-r6, lr}
		;((end - start) / 4) + 1
		subs r3, r1, r0        ; r3 = end - start
        lsrs r3, r3, #2        ; r3 = (end - start) / 4
        adds r3, r3, #1        ; incluir la última palabra
        movs r4, r0            ; r4 = puntero a memoria (start)
        movs r5, r2            ; r5 = puntero a buffer
        movs r6, r3            ; r6 = contador
loop
		cmp r6, #0
		beq end_md
		ldr r1, [r4]           ; leer dato de memoria
        str r1, [r5]           ; guardarlo en buffer
        adds r4, r4, #4        ; avanzar dirección de memoria
        adds r5, r5, #4        ; avanzar buffer
        subs r6, r6, #1        ; decrementar contador
        b loop
end_md
		pop{r3-r6, lr}
		end