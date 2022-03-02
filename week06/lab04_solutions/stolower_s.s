@ stolower_s - covert upper case chars to lower case chars in s
.global stolower_s

@ r0 - char *s
stolower_s:

stolower_loop:
    ldrb r1, [r0]
    cmp r1, #0
    beq stolower_exit
    cmp r1, #'A'
    blt stolower_increment
    cmp r1, #'Z'
    bgt stolower_increment
    add r1, r1, #32
    strb r1, [r0]
stolower_increment:
    add r0, r0, #1
    b stolower_loop

stolower_exit:
    bx lr
