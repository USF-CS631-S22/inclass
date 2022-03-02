@ max3_s.s - find the maximum value of three arguments using max2
.global max3_s

@ r0 - int v0
@ r1 - int v1
max2_s:
    
    cmp r0, r1
    ble max2_else
    b max2_end
max2_else:
    mov r0, r1
max2_end:
    bx lr

max2_opt_s:
    cmp r0, r1
    movle r0, r1
    bx lr

@ r0 - int v0
@ r1 - int v1
@ r2 - int v2
max3_s:
    sub sp, sp, #8
    str lr, [sp]

    str r2, [sp, #4]
    bl max2_s
    @ r0 = max2_s(r0, r1)

    ldr r1, [sp, #4]
    bl max2_s

    ldr lr, [sp]
    add sp, sp, #8
    bx lr
