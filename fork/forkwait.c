/**
 * Demonstrate the use of wait() after fork() to wait for a child process to terminate.
 *
 * Adapted from:
 * https://man7.org/tlpi/code/online/dist/procexec/t_fork.c.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int idata = 111;

int
main(void)
{
    int istack = 222;
    pid_t childPid;

    switch (childPid = fork()) {
    case -1: /* error */
        perror("fork");
        exit(EXIT_FAILURE);

    case 0: /* child */
        idata *= 3;
        istack *= 3;
        break;

    default: /* parent */
        printf("PID=%ld will wait for one child to terminate...\n",
               (long) getpid());

        if (wait(NULL) == -1) {    // wait for any one child to terminate
            perror("wait");
            exit(EXIT_FAILURE);
        }
        break;
    }

    printf("PID=%ld %s idata=%d istack=%d\n",
           (long) getpid(),
           (childPid == 0) ? "(child) " : "(parent)",
           idata,
           istack);

    exit(EXIT_SUCCESS);
}
