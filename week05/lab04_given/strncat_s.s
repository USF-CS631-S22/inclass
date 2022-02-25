@ strncat_s concatentate two strings
.global strncat_s

@ r0 - char *dest
@ r1 - char *src
@ r2 - int n
strncat_s:
    bx lr
