.global main

main:
    mov r1, #3
    mov r2, #3
    add r0, r1, r2, lsr #1
    mov r1, #3
    mov r2, #3
    add r0, r1, r2
    lsr r0, r0, #1
    bx lr
