mov sp, #255
lsl sp, sp, #2

sub sp, sp, #8
mov r0, #1
mov ip, #1
str r0, [sp, #4]            @ HACK: offset must match ip << 2 so this test doesn't need RD2
mov r0, #2                  @ make r0 something else so the ldr is a good test
ldr r0, [sp, ip, lsl #2]    @r0 should be 1
add r0, r0, #0
