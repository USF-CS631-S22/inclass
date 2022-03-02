.global get_bitseq_signed_s

@ r0 - num
@ r1 - start
@ r2 - end

@ r3 - len
@ r4 - shift_amt

get_bitseq_signed_s:
    sub sp, sp, #8
    str lr, [sp]
    str r4, [sp, #4]

    sub r4, r2, r1  
    add r4, r4, #1    @ Compute len of sequence
    mov r12, #32
    sub r4, r12, r4   @ Compute shift amount for sign extension

    bl get_bitseq_s

    lsl r0, r0, r4    @ Move all bits to the far left
    asr r0, r0, r4    @ Move all bits back, with sign bit repeated

    ldr r4, [sp, #4]
    ldr lr, [sp]
    add sp, sp, #8
    bx lr
    
