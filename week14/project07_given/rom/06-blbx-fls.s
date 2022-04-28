main:
    mov r0, #2
    bl foo
    add r0, r0, #0  @ marker instruction
foo:
    add r0, r0, #4  @ r0 should be 6
    bx lr
