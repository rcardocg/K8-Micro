        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8
        EXPORT BFASM

BFASM
        push {r4, lr}

        movs r4, r0        ; r4 = start

loop
        cmp r4, r1
        bgt end_bf

        cmp r3, #4
        beq bf_word
        cmp r3, #2
        beq bf_half
        cmp r3, #1
        beq bf_byte
        b end_bf

bf_word
        str r2, [r4]
        b bf_next

bf_half
        strh r2, [r4]
        b bf_next

bf_byte
        strb r2, [r4]

bf_next
        add r4, r4, r3
        b loop

end_bf
        pop {r4, lr}
        bx lr
        end
