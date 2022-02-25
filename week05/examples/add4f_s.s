@ Example of how to call a function from ARM assembly code
@
@ In this example, add4f_s makes two calls to add2f_s to
@ add 4 numbers.
.global add4f_s

@ r0 - int a0
@ r1 - int a1
add2f_s:
    add r0, r0, r1
    bx lr

@ r0 - int a0
@ r1 - int a1
@ r2 - int a2
@ r3 - int a3
add4f_s:
    sub sp, sp, #16
    str lr, [sp]

    str r2, [sp, #8]
    str r3, [sp, #12]

    bl add2f_s
    @ r0 = a0 + a1

    ldr r3, [sp, #12]
    ldr r2, [sp, #8]

    str r0, [sp, #4]

    mov r0, r2
    mov r1, r3
    bl add2f_s
    @ r0 = a2 + a3

    ldr r1, [sp, #4]
    add r0, r0, r1

    ldr lr, [sp]
    add sp, sp, #16
    bx lr
