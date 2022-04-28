main:
    mov r1, #1
    nop
    nop
    mov r2, #2
    nop
    nop
    bl first
    nop
    nop
    nop
    nop
    add r0, r0, #0      @ end marker        
    nop
    nop
    nop
    nop

first:
    add r0, r1, r2
    nop
    nop
    add r0, r0, #1
    nop
    nop
    bx lr
    nop
    nop
    nop
    nop
