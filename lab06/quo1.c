#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int pid, arrival, burst, bt_left, priority, completion, waiting, turnaround, start;
    int finished;
} Process;

void inputProcesses(Process p[], int *n, int isPriority) {
    printf("Enter number of processes: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &p[i].burst);
        if (isPriority) {
            printf("Process %d - Priority (lower = higher priority): ", i + 1);
            scanf("%d", &p[i].priority);
        }
        p[i].pid = i + 1;
        p[i].bt_left = p[i].burst;
        p[i].finished = 0;
    }
}

void calculateAndDisplay(Process p[], int n) {
    float avgTAT = 0, avgWT = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        avgTAT += p[i].turnaround;
        avgWT += p[i].waiting;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    }
    printf("Average Turnaround Time: %.2f\n", avgTAT / n);
    printf("Average Waiting Time: %.2f\n", avgWT / n);
}

// 1. Preemptive SJF
void sjfPreemptive(Process p[], int n) {
    int complete = 0, time = 0, min_index = -1, shortest = 1e9;
    while (complete < n) {
        shortest = 1e9;
        min_index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].bt_left > 0 && p[i].bt_left < shortest) {
                shortest = p[i].bt_left;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        if (p[min_index].bt_left == p[min_index].burst)
            p[min_index].start = time;

        p[min_index].bt_left--;
        time++;

        if (p[min_index].bt_left == 0) {
            p[min_index].completion = time;
            p[min_index].finished = 1;
            complete++;
        }
    }

    calculateAndDisplay(p, n);
}

// 2. Round Robin
void roundRobin(Process p[], int n) {
    int time = 0, tq, done = 0;
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int remain = n, i = 0;
    while (remain > 0) {
        int executed = 0;
        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].bt_left > 0) {
                executed = 1;
                if (p[i].bt_left == p[i].burst)
                    p[i].start = time;

                if (p[i].bt_left <= tq) {
                    time += p[i].bt_left;
                    p[i].bt_left = 0;
                    p[i].completion = time;
                    p[i].finished = 1;
                    remain--;
                } else {
                    p[i].bt_left -= tq;
                    time += tq;
                }
            }
        }
        if (!executed) time++;
    }

    calculateAndDisplay(p, n);
}

// 3. Non-Preemptive Priority
void priorityScheduling(Process p[], int n) {
    int time = 0, complete = 0;
    while (complete < n) {
        int idx = -1, best_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].finished) {
                if (p[i].priority < best_priority) {
                    best_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].start = time;
        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].finished = 1;
        complete++;
    }

    calculateAndDisplay(p, n);
}

// Reset processes
void resetProcesses(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].bt_left = p[i].burst;
        p[i].finished = 0;
    }
}

// Menu
int main() {
    Process p[MAX];
    int n, choice;
    while (1) {
        printf("\n--- CPU Scheduling Algorithms ---\n");
        printf("1. Preemptive Shortest Job First (SJF)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Non-Preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                inputProcesses(p, &n, 0);
                sjfPreemptive(p, n);
                break;
            case 2:
                inputProcesses(p, &n, 0);
                roundRobin(p, n);
                break;
            case 3:
                inputProcesses(p, &n, 1);
                priorityScheduling(p, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
