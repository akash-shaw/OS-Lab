#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Structure to store process details
struct Process {
    int id, bt, at, wt, tat, rt, priority;
};

void findWaitingTime(struct Process p[], int n) {
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].bt + p[i-1].wt;
    }
}

void findTurnAroundTime(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
    }
}

void findAvgTime(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt/n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat/n);
}

void preemptiveSJF(struct Process p[], int n) {
    int completed = 0, t = 0, min_bt, shortest;
    int remain_bt[MAX];
    for (int i = 0; i < n; i++) remain_bt[i] = p[i].bt;

    while (completed < n) {
        min_bt = 10000; // A large number
        shortest = -1;
        
        // Find process with the shortest burst time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && remain_bt[i] > 0 && remain_bt[i] < min_bt) {
                min_bt = remain_bt[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            t++;
            continue;
        }

        // Process the shortest job
        remain_bt[shortest]--;
        if (remain_bt[shortest] == 0) {
            completed++;
            p[shortest].wt = t + 1 - p[shortest].at - p[shortest].bt;
            p[shortest].tat = p[shortest].wt + p[shortest].bt;
        }
        t++;
    }
    findAvgTime(p, n);
}

void roundRobin(struct Process p[], int n, int quantum) {
    int completed = 0, t = 0;
    int remain_bt[MAX];
    int remaining_processes = n;
    
    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remain_bt[i] = p[i].bt;
    }

    while (completed < n) {
        int all_done = 1; // Flag to check if all processes are completed in this iteration

        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and not yet completed
            if (remain_bt[i] > 0 && p[i].at <= t) {
                all_done = 0; // There's still some work to be done

                // Process the current process for up to 'quantum' time or the remaining burst time
                if (remain_bt[i] <= quantum) {
                    t += remain_bt[i];
                    p[i].wt = t - p[i].at - p[i].bt;  // Waiting time = current time - arrival time - burst time
                    p[i].tat = p[i].wt + p[i].bt;     // Turnaround time = waiting time + burst time
                    remain_bt[i] = 0;                 // Process is completed
                    completed++;
                } else {
                    t += quantum;           // Increase time by quantum for this process
                    remain_bt[i] -= quantum; // Reduce remaining burst time of the process
                }
            }
        }

        // If no process was done in this round (i.e., all processes are waiting to arrive), increment time
        if (all_done) {
            t++; // Increase time when no processes are ready yet
        }
    }
    findAvgTime(p, n);  // Calculate and print the average waiting time and turnaround time
}

void nonPreemptivePriority(struct Process p[], int n) {
    int completed = 0, t = 0;
    int min_priority, selected;
    while (completed < n) {
        min_priority = 10000; // A large number
        selected = -1;
        
        // Select the process with the highest priority (lowest priority number)
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                selected = i;
            }
        }

        if (selected != -1) {
            t += p[selected].bt;
            p[selected].wt = t - p[selected].at - p[selected].bt;
            p[selected].tat = p[selected].wt + p[selected].bt;
            completed++;
        } else {
            t++;
        }
    }
    findAvgTime(p, n);
}

int main() {
    int n, choice, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter the process details (ID, Arrival Time, Burst Time, Priority):\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (lower value means higher priority): ");
        scanf("%d", &p[i].priority);
    }

    do {
        printf("\nMenu:\n");
        printf("1. Preemptive Shortest Job First (SJF)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Non-Preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                preemptiveSJF(p, n);
                break;
            case 2:
                printf("Enter Time Quantum for Round Robin: ");
                scanf("%d", &quantum);
                roundRobin(p, n, quantum);
                break;
            case 3:
                nonPreemptivePriority(p, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again!\n");
        }
    } while (choice != 4);

    return 0;
}
