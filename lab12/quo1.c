#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int exec_time;
    int period;
    int deadline;
    int next_release;
    int remaining_time;
} Task;

int lcm(int a, int b) {
    int max = (a > b) ? a : b;
    while (1) {
        if (max % a == 0 && max % b == 0) return max;
        max++;
    }
}

int get_hyperperiod(Task *tasks, int n) {
    int h = tasks[0].period;
    for (int i = 1; i < n; i++)
        h = lcm(h, tasks[i].period);
    return h;
}

void rate_monotonic(Task *tasks, int n) {
    int time = 0, hyperperiod = get_hyperperiod(tasks, n);
    printf("\nRate-Monotonic Scheduling:\n");

    for (int i = 0; i < n; i++) {
        tasks[i].next_release = 0;
        tasks[i].remaining_time = 0;
    }

    while (time < hyperperiod) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release) {
                tasks[i].remaining_time = tasks[i].exec_time;
                tasks[i].next_release += tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 &&
                (selected == -1 || tasks[i].period < tasks[selected].period)) {
                selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }
        time++;
    }
}

void earliest_deadline_first(Task *tasks, int n) {
    int time = 0, hyperperiod = get_hyperperiod(tasks, n);
    printf("\nEarliest-Deadline-First Scheduling:\n");

    for (int i = 0; i < n; i++) {
        tasks[i].next_release = 0;
        tasks[i].remaining_time = 0;
        tasks[i].deadline = tasks[i].period;
    }

    while (time < hyperperiod) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release) {
                tasks[i].remaining_time = tasks[i].exec_time;
                tasks[i].deadline = time + tasks[i].period;
                tasks[i].next_release += tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 &&
                (selected == -1 || tasks[i].deadline < tasks[selected].deadline)) {
                selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }
        time++;
    }
}

int main() {
    int n = 3;
    Task *tasks = (Task *)malloc(n * sizeof(Task));

    // Hardcoded input: ID, Execution Time, Period
    tasks[0] = (Task){1, 1, 4, 0, 0, 0};  // Task 1: exec=1, period=4
    tasks[1] = (Task){2, 2, 5, 0, 0, 0};  // Task 2: exec=2, period=5
    tasks[2] = (Task){3, 1, 20, 0, 0, 0}; // Task 3: exec=1, period=20

    int choice;
    do {
        printf("\nReal-Time Scheduling Algorithms:\n");
        printf("1. Rate-Monotonic (RMS)\n");
        printf("2. Earliest-Deadline-First (EDF)\n");
        printf("3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: rate_monotonic(tasks, n); break;
            case 2: earliest_deadline_first(tasks, n); break;
            case 3: break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 3);

    free(tasks);
    return 0;
}
