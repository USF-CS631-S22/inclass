@ Sum an array of numbers
.global sum_array_s

@ r0 - int *array
@ r1 - int len

@ r2 - i
@ r3 - sum

sum_array_s:
    mov r2, #0       @ i = 0
    mov r3, #0       @ sum = 0

loop:
    cmp r2, r1
    beq loop_exit    
    ldr r12, [r0]    @ r12 = *array
    add r3, r3, r12  @ sum = sum + r1
    add r2, r2, #1   @ i = i + 1
    add r0, r0, #4   @ array = array + 4 (next int)
    b loop

loop_exit:
    mov r0, r3       @ r0 = sum (return value)
    bx lr
