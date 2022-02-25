@ Recursive factorial
.global fact_s

@ r0 - int n

fact_s:
    sub sp, sp, #8   @ Allocate 8 bytes (two words) on the stack
                     @ We much allocate the stack in multiples of 8
    str lr, [sp]     @ Preserver lr because bl will overwrite this value

    cmp r0, #0       @ Compare n to 0
    bne rec_step     @ Go to rec step if n != 0
    mov r0, #1       @ n == 0, so set r = 1
    b exit           @ Need to exit properly below
    
rec_step:  
    str r0, [sp, #4] @ r0 is caller-saved, so put on stack
    sub r0, r0, #1   @ n = n - 1
    bl fact_s        @ fact_s(n - 1)
    ldr r1, [sp, #4] @ restore n from stack into r1
    mul r0, r1, r0   @ fact_s(n - 1) * n

exit:
    ldr lr, [sp]     @ Restore lr so we can return to caller
    add sp, sp, #8   @ Deallocate stack space
    bx lr            @ Return
