#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(char *arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s str1 str2 str3 ...\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork Failed!");
        return 1;
    }

    if (pid == 0) {
        // Child Process: Sort and display
        bubbleSort(&argv[1], argc - 1);
        printf("Child: Sorted strings:\n");
        for (int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } else {
        // Parent Process: Wait for child then display unsorted
        wait(NULL);
        printf("Parent: Unsorted strings:\n");
        for (int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }

    return 0;
}
