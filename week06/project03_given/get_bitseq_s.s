.global get_bitseq_s


@ r0 - num
@ r1 - start
@ r2 - end / mask

@ r3 - val
@ r12 - len
@ r4 - mask

get_bitseq_s:
    sub r12, r2, r1
    add r12, r12, #1            @ Compute len of bit sequence
    lsr r3, r0, r1              @ Move sequence to beginning of word

    cmp r12, #32                
    bne get_bitseq_mask_less_32 @ Check if len is 32, special case
    ldr r2, =#0xFFFFFFFF        @ Set mask to 0xFFFFFFFF
    b get_bitseq_and

get_bitseq_mask_less_32:        
    mov r2, #1                  @ Create mask for len < 32
    lsl r2, r2, r12
    sub r2, r2, #1    

get_bitseq_and:
    and r3, r3, r2
    mov r0, r3
    bx lr
