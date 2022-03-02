.global substr_s
.global matches_s

/*

r0 - char *s1
r1 - char *s2

r2 - char *p1
r3 - char *p2

*/

substr_s:
    bx lr

/*

r0 - char *s1
r1 - char *s2

*/

matches_s:
    bx lr
