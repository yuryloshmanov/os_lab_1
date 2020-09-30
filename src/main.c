#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (pid == 0) {
        char file_name[50];
        printf("Enter file name: ");
        scanf("%[^\n]%*c", file_name);
        FILE *f = fopen(file_name, "r");

        dup2(fileno(f), STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd[1], STDERR_FILENO);

        close(fd[0]);
        close(fd[1]);
        fclose(f);

        execl("child", "child", (char *) NULL);
    } else {
        close(fd[1]);
        waitpid(pid, (int *)NULL, 0);

        float result;
        read(fd[0], &result, sizeof(result));
        printf("%f\n", result);

        close(fd[0]);
    }
    return 0;
}
