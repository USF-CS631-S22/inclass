#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    int id;
    int r;
    char *argv[4];
    argv[0] = "hello";
    argv[1] = 0;
    int fd;
    char buf[128];
    int n;

    id = fork();

    if (id == 0) {
        /* we are in the child */
        /* close stdout */
        close(1);
        /* open file and occupy stdout */
        fd = open("hello.out", O_WRONLY | O_CREATE);
        if (fd < 0) {
            printf("Cannot open hello.out\n");   
        }
        exec(argv[0], argv);
        printf("Child: WE DON'T SEE THIS\n");
        exit(0);
    } else {
        /* we are in the parent */
        id = wait(&r);

        fd = open("hello.out", O_RDONLY);
        if (fd < 0) {
            printf("Cannot open hello.out\n");
        }
        n = read(fd, buf, 128);
        buf[n] = '\0';
        printf("hello.out:\n%s", buf);
        printf("Parent: child terminated\n");
    }

    exit(0);
}
