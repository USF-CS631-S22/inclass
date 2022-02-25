@ Add 4 numbers
.global add4f_s

@ r0 - int a0
@ r1 - int a1
add2_s:
    add r0, r0, r1
    bx lr

@ r0 - int a0
@ r1 - int a1
@ r2 - int a2
@ r3 - int a3
add4f_s:
    sub sp, sp, #16   @ Allocate 16 bytes (4 words) on the stack
    str lr, [sp]      @ Store lr value on stack

    str r2, [sp, #4]  @ r2 is caller saved
    str r3, [sp, #8]  @ r3 is caller saved
    bl add2_s
    @ r0 = a0 + a1
    str r0, [sp, #12] @ r0 is caller saved

    ldr r0, [sp, #4]  @ Set r0 to a2
    ldr r1, [sp, #8]  @ Set r1 to a3
    bl add2_s
    @ r0 = a2 + a3
    ldr r1, [sp, #12] @ Restore previous r0 into r1
    add r0, r1, r0    @ Add (a0 + a1) + (a2 + a3)

    ldr lr, [sp]      @ Restore lr
    add sp, sp, #16   @ Deallocate 16 bytes (4 words) of the stack
    bx lr             @ Return to caller
