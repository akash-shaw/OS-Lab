#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork Failed!");
        return 1;
    }

    if (pid == 0) {
        // Child Process
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID (PPID): %d\n", getppid());
    } else {
        // Parent Process
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }

    return 0;
}
