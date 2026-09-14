/**
 * Demonstrate the use of fork(), showing that parent and child
 * get separate copies of stack and data segments.
 *
 * Adapted from:
 * https://man7.org/tlpi/code/online/dist/procexec/t_fork.c.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static int idata = 111;

int
main(void)
{
    int istack = 222;
    pid_t childPid;

    switch (childPid = fork()) {
    case -1: // error
        perror("fork");
        exit(EXIT_FAILURE);

    case 0: // child
        idata *= 3;
        istack *= 3;
        break;

    default: // parent
        int secs = 3;
        printf("PID=%ld will sleep %d seconds...\n", (long) getpid(), secs);
        sleep(secs);
        break;
    }

    printf("PID=%ld %s idata=%d istack=%d\n",
           (long) getpid(),
           (childPid == 0) ? "(child) " : "(parent)",
           idata, istack);

    exit(EXIT_SUCCESS);
}
