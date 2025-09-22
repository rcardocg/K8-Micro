		AREA | .text |, CODE, READONLY, ALIGN = 2
        THUMB
        REQUIRE8
        PRESERVE8
        EXPORT MMASM

MMASM
        push{lr}
		str r1, [r0]
		
		pop{pc}
		end

