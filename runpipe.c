#include "smallsh.h"

int runpipe(char *arg1[], char *arg2[]) {
    int fd[2], status;
    pid_t pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe");
        return -1;
    }

    if ((pid1 = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (pid1 == 0) {
        // 첫 번째 자식 프로세스
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execvp(arg1[0], arg1);
        perror("execvp");
        exit(1);
    }

    if ((pid2 = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (pid2 == 0) {
        // 두 번째 자식 프로세스
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execvp(arg2[0], arg2);
        perror("execvp");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    return status;
}
