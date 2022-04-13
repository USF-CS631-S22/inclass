main:
    mov r1, #1
    cmp r1, #2
    ble foo
    mov r0, #0
    add r0, r0, #0  @ shouldn't stop here
foo:
    mov r0, #1
    add r0, r0, #0  @ should stop here with r0 == 1
