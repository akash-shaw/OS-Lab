#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10  // max processes
#define MAX_R 10  // max resources

int n, m; // Number of processes and resources

int Available[MAX_R];
int Max[MAX_P][MAX_R];
int Allocation[MAX_P][MAX_R];
int Need[MAX_P][MAX_R];

// Function to calculate Need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

// Safety Algorithm
bool isSafe() {
    int Work[MAX_R];
    bool Finish[MAX_P] = {false};

    for (int i = 0; i < m; i++)
        Work[i] = Available[i];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];
                    Finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            return false; // not safe
        }
    }
    return true;
}

// Resource Request Algorithm
bool requestResources(int pid, int Request[]) {
    // Step 1: Check if Request <= Need
    for (int i = 0; i < m; i++) {
        if (Request[i] > Need[pid][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Step 2: Check if Request <= Available
    for (int i = 0; i < m; i++) {
        if (Request[i] > Available[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Step 3: Pretend to allocate
    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[pid][i] += Request[i];
        Need[pid][i] -= Request[i];
    }

    // Check if new state is safe
    if (isSafe()) {
        printf("Request granted. System remains in a safe state.\n");
        return true;
    } else {
        // Rollback
        for (int i = 0; i < m; i++) {
            Available[i] += Request[i];
            Allocation[pid][i] -= Request[i];
            Need[pid][i] += Request[i];
        }
        printf("Request cannot be granted. System would be unsafe.\n");
        return false;
    }
}

// Print current state
void printState() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", Allocation[i][j]);
        printf("\t\t");
        for (int j = 0; j < m; j++) printf("%d ", Max[i][j]);
        printf("\t\t");
        for (int j = 0; j < m; j++) printf("%d ", Need[i][j]);
        printf("\n");
    }
    printf("Available: ");
    for (int i = 0; i < m; i++) printf("%d ", Available[i]);
    printf("\n");
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter Available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &Available[i]);

    calculateNeed();

    printState();

    if (isSafe())
        printf("System is initially in a SAFE state.\n");
    else {
        printf("System is in an UNSAFE state. Exiting.\n");
        return 0;
    }

    int choice;
    do {
        printf("\n1. Make a resource request\n2. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int pid, Request[MAX_R];
            printf("Enter process number (0 to %d): ", n - 1);
            scanf("%d", &pid);
            printf("Enter resource request vector:\n");
            for (int i = 0; i < m; i++)
                scanf("%d", &Request[i]);

            requestResources(pid, Request);
            printState();
        }
    } while (choice != 2);

    return 0;
}
