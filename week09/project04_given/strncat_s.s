@ strncat_s concatentate two strings

.global strncat_s

@ r0 - char *dest
@ r1 - char *src
@ r2 - int n

@ r3 - int i
strncat_s:
    mov r3, #0

strncat_loop1:
    ldrb r12, [r0]
    cmp r12, #0
    beq strncat_loop2
    add r0, r0, #1
    b strncat_loop1

strncat_loop2:
    cmp r3, r2
    bge strncat_loop2_exit
    ldrb r12, [r1]
    cmp r12, #0
    beq strncat_loop2_exit
    strb r12, [r0]
    add r0, r0, #1
    add r1, r1, #1
    add r3, r3, #1
    b strncat_loop2
    
strncat_loop2_exit:
    mov r12, #0
    strb r12, [r0]
    bx lr
