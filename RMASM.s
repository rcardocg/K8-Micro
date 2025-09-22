        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8
			
        EXPORT	RMASM

RMASM
		push{lr}
		cmp r0, #0
		beq mod_r0
		cmp r0, #1
		beq mod_r1
		cmp r0, #2
		beq mod_r2
		cmp r0, #3
		beq mod_r3
		cmp r0, #4
		beq mod_r4
		cmp r0, #5
		beq mod_r5
		cmp r0, #6
		beq mod_r6
		cmp r0, #7
		beq mod_r7
		cmp r0, #8
		beq mod_r8
		cmp r0, #9
		beq mod_r9
		cmp r0, #10
		beq mod_r10
		cmp r0, #11
		beq mod_r11
		cmp r0, #12
		beq mod_r12
		; r13 (SP) no se toca
		cmp r0, #13
		beq end_rm
		; r14 (LR) no se toca
		cmp r0, #14
		beq end_rm
		; r15 (PC) no se toca
		cmp r0, #15
		beq end_rm

mod_r0
	mov r0, r1
	b end_rm
mod_r1
	mov r1, r1
	b end_rm
mod_r2
	mov r2, r1
	b end_rm
mod_r3
	mov r3, r1
	b end_rm
mod_r4
	mov r4, r1
	b end_rm
mod_r5
	mov r5, r1
	b end_rm
mod_r6
	mov r6, r1
	b end_rm
mod_r7
	mov r7, r1
	b end_rm
mod_r8
	mov r8, r1
	b end_rm
mod_r9
	mov r9, r1
	b end_rm
mod_r10
	mov r10, r1
	b end_rm
mod_r11
	mov r11, r1
	b end_rm
mod_r12
	mov r12, r1
	b end_rm
	
end_rm
	
	pop{pc}

		end