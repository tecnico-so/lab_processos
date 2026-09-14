/**
 * A simple example of fork(), exec(), and waitpid() to wait for a specific child process to terminate.
 *
 * Adapted from:
 * https://man7.org/tlpi/code/online/dist/procexec/simple_system.c.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
run_ls(void)
{
    int status;
    pid_t childPid;

    switch (childPid = fork()) {
    case -1: /* error */
        return -1;

    case 0: /* child */
        execl("/bin/ls", "ls", "-la", (char *) NULL);

        /*
         * exec variants differ in how arguments are passed,
         * whether PATH is searched, and whether a custom
         * environment is supplied.
         *
         *   l = list
         *   v = vector
         *   p = PATH search
         *   e = environment
         *
         * All variants replace the current program if successful.
         */

        /* exec returns only if an error occurred */
        _exit(127); // this value is convention for "command could not be executed"

    default: /* parent */
        printf("PID=%ld will wait for child %ld to terminate...\n",
               (long) getpid(), (long) childPid);
        if (waitpid(childPid, &status, 0) == -1)
            return -1;
        printf("PID=%ld (parent)\n", (long) getpid());
        
        return status;
    }
}

int
main(void)
{
    int status;

    status = run_ls();

    if (status == -1) {
        perror("run_ls");
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status))          // child terminated normally
        return WEXITSTATUS(status); // return the child's exit code

    return EXIT_FAILURE;
}
