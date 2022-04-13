main:
    mov r0, #1          @ Initial sp to top of RAM (1024)
    lsl sp, r0, #10

    sub sp, sp, #20     @ allocate stack space for params
    mov r0, #0
    str r0, [sp]
    mov r0, #4
    str r0, [sp, #4]
    mov r0, #8
    str r0, [sp, #8]
    mov r0, #12
    str r0, [sp, #12]
    mov r0, #16
    str r0, [sp, #16]
    mov r0, sp
    mov r1, #5          @ len = 5
    bl sum_array_s      @ sum(0, 4, 8, 12, 16) = 40
    add r0, r0, #0      @ end marker

sum_array_s:
    mov r2, #0
    mov r3, #0

sum_array_loop:
    cmp r3, r1
    bge sum_array_loop_exit
    ldr r12, [r0]
    add r2, r2, r12
    add r0, r0, #4
    add r3, r3, #1
    b sum_array_loop

sum_array_loop_exit:    
    mov r0, r2
    bx lr
