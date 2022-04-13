mov sp, #255
lsl sp, sp, #2

sub sp, sp, #8
mov r0, #1
str r0, [sp, #4]
mov r0, #2          @ make r0 something else so the ldr is a good test
ldr r0, [sp, #4]    @ r0 should be 1
add r0, r0, #0
