void strncat_c(char *dest, char *src, int n) {
    int i = 0;

    while (*dest != '\0') {
        dest += 1;
    }
    
    while ((i < n) && (*src != '\0')) {
        *dest = *src;
        dest += 1;
        src += 1;
        i += 1;   
    }

    *dest = '\0';
}
