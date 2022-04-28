main:
    mov r1, #1
    mov r2, #2
    add r0, r1, r2   @ r0 should be 3
    add r0, r0, #0   @ marker instruction
