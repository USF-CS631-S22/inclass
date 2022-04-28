main:
    mov r1, #1
    mov r2, #2
    add r0, r1, r2
    add r0, r0, #1
    mov r3, #0
    mov r4, #99
    str r4, [r3]
    ldr r5, [r3]
    add r0, r5, #1      @ r0 should be 100
    add r0, r0, #0      @ end marker
    nop
    nop
    nop
    nop
