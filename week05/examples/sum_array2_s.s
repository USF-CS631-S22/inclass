@ Sum an array of numbers using an index in ldr
.global sum_array2_s

@ r0 - int *array
@ r1 - int len

@ r2 - i
@ r3 - sum

sum_array2_s:
    mov r2, #0                 @ i = 0
    mov r3, #0                 @ sum = 0

loop:
    cmp r2, r1
    beq loop_exit    
    ldr r12, [r0, r2, lsl #2]  @ r12 = *(array + (r2 << 2))
    add r3, r3, r12            @ sum = sum + r1
    add r2, r2, #1             @ i = i + 1
    b loop

loop_exit:
    mov r0, r3                 @ r0 = sum (return value)
    bx lr
