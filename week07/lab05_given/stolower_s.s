/* stolower_s - covert upper case chars to lower case chars in s */

.global stolower_s

/*

r0 - char *s

*/

stolower_s:

loop:    
    ldrb r1, [r0]
    cmp r1, #0
    beq end
    cmp r1, #65
    blt skip
    cmp r1, #90
    bgt skip
    add r1, r1, #32
    strb r1, [r0]
skip:
    add r0, r0, #1
    b loop
end:
    bx lr
