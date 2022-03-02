@ fib_rec_s - recursive fibanocci

.global fib_rec_s

@ r0 - int n
fib_rec_s:
    sub sp, sp, #16
    str lr, [sp]

    cmp r0, #1
    ble fib_rec_exit

fib_rec_step:
    str r0, [sp, #4]
    sub r0, r0, #1
    bl fib_rec_s
    @ r0 = fib_rec_s(n - 1)
    str r0, [sp, #8]
    ldr r0, [sp, #4]
    sub r0, r0, #2
    bl fib_rec_s
    ldr r1, [sp, #8]
    add r0, r0, r1

fib_rec_exit:
    ldr lr, [sp]
    add sp, sp, #16
    bx lr
