#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    int id;
    int p[2];

    char *arg_ls[4];
    arg_ls[0] = "ls";
    arg_ls[1] = 0;

    char *arg_wc[4];
    arg_wc[0] = "wc";
    arg_wc[1] = 0;


    pipe(p);

    id = fork();

    if (id == 0) {
        /* we are in the ls child */
        close(p[0]);
        close(1);
        dup(p[1]);
        close(p[1]);
        exec(arg_ls[0], arg_ls);
        printf("Child: WE DON'T SEE THIS\n");
        exit(0);
    }

    id = fork();

    if (id == 0) {
        /* we are in the wc child */
        close(p[1]);
        close(0);
        dup(p[0]);
        close(p[0]);
        exec(arg_wc[0], arg_wc);
        printf("Child: WE DON'T SEE THIS\n");
        exit(0);
    }

    close(p[0]);
    close(p[1]);

    wait(0);
    wait(0);

    printf("Parent done.\n");

    exit(0);
}
