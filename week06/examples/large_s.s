.global main

main:
    ldr r0, =#0xFFAA1122


    @str r0, [r1]
    
    @ str =#0x2013, [r0] NO


    @ 0xFFAA1122

    mov r0, #0
    mov r1, #0xFF
    orr r0, r0, r1
    lsl r0, r0, #8
    mov r1, #0xAA
    orr r0, r0, r1
    lsl r0, r0, #8
    mov r1, #0x11
    orr r0, r0, r1
    lsl r0, r0, #8
    mov r1, #0x22
    orr r0, r0, r1

    bx lr
