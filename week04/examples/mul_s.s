.global mul_s

@ r0 - int a0
@ r1 - int a1
@ r2 - int a2
mul_s:
    mul r0, r0, r1  @ r0 = a0 * a1
    mul r0, r0, r2  @ r0 = r0 * a2
    bx lr
