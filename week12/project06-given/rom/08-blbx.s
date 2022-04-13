mov r0, #1
mov r1, #2
bl func
add r0, r0, #0  @ r1 should be 3
func:
    add r0, r0, r1
    bx lr
