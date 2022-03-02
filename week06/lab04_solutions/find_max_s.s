@ find_max_s - find the maximum value in an interger array
.global find_max_s


@ r0 - int *array
@ r1 - int n

@ r2 - int i
@ r3 - max
find_max_s:
    ldr r3, [r0]
    mov r2, #1

find_max_loop:
    cmp r2, r1
    bge find_max_exit

    ldr r12, [r0, r2, lsl #2]
    cmp r12, r3
    ble find_max_less
    mov r3, r12

find_max_less:
    add r2, r2, #1
    b find_max_loop

find_max_exit:
    mov r0, r3
    bx lr
