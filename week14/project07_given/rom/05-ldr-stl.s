main:
    mov r0, #0
    mov r1, #1
    str r1, [r0]
    ldr r2, [r0]
    add r0, r2, #1   @ r0 should be 2
    add r0, r0, #0   @ marker instruction
