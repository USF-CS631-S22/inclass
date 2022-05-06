#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    int id;
    int p[2];
    char buf[100];
    int n;

    pipe(p);
    
    id = fork();

    if (id == 0) {
        /* we are in the child */
        close(p[0]);
        write(p[1], "hello parent", 12);
        exit(0);
    } else {
        /* we are in the parent */
        close(p[1]);            
        n = read(p[0], buf, 100);
        buf[n] = '\0';
        printf("From child: %s\n", buf);
    }

    exit(0);
}
