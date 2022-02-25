@ String length
.global strlen_s

@ r0 = char *s

@ r1 = len (counter)

strlen_s:
    mov r1, #0

loop:    
    ldrb r2, [r0]
    cmp r2, #0
    beq exit
    add r1, r1, #1
    add r0, r0, #1
    b loop
exit:
    mov r0, r1
    bx lr
