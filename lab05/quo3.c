#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

void bubbleSort(char *arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (strcmp(arr[j], arr[j+1]) > 0) {
                char *tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

void selectionSort(char *arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (strcmp(arr[j], arr[min]) < 0)
                min = j;
        if (min != i) {
            char *tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);
    getchar();  // consume newline

    char *arr[n];
    for (int i = 0; i < n; i++) {
        char temp[MAX];
        printf("Enter string %d: ", i + 1);
        fgets(temp, MAX, stdin);
        temp[strcspn(temp, "\n")] = 0; // remove newline
        arr[i] = strdup(temp);
    }

    pid_t pid1 = fork();

    if (pid1 == 0) {
        bubbleSort(arr, n);
        printf("\nChild 1 (Bubble Sort):\n");
        for (int i = 0; i < n; i++) printf("%s ", arr[i]);
        printf("\n");
        exit(0);
    } else {
        pid_t pid2 = fork();

        if (pid2 == 0) {
            selectionSort(arr, n);
            printf("\nChild 2 (Selection Sort):\n");
            for (int i = 0; i < n; i++) printf("%s ", arr[i]);
            printf("\n");
            exit(0);
        } else {
            // Parent waits until any one child finishes
            wait(NULL);
            printf("\nParent: One child has finished sorting.\n");
        }
    }

    return 0;
}
