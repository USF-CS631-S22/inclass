void stolower_c(char *s) {
    while (*s != '\0') {
        if ((*s >= 'A') && (*s <= 'Z')) {
            *s = *s + 32;
        }
        s += 1;
    }
}
