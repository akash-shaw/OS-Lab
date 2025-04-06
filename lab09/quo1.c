#include <stdio.h>

#define MAX 10

struct Hole {
    int size, original, id;
};

struct Process {
    int size, allocatedHole; // -1 means not allocated
};

void resetHoles(struct Hole holes[], int n) {
    for (int i = 0; i < n; i++)
        holes[i].size = holes[i].original;
}

void printResult(struct Process p[], int np, struct Hole h[], int nh, const char *type) {
    printf("\n=== %s Result ===\n", type);
    for (int i = 0; i < np; i++) {
        if (p[i].allocatedHole != -1)
            printf("Process %d (size %d) -> Hole %d\n", i, p[i].size, p[i].allocatedHole);
        else
            printf("Process %d (size %d) -> Not Allocated\n", i, p[i].size);
    }

    printf("\nHole Status:\n");
    for (int i = 0; i < nh; i++)
        printf("Hole %d: Original = %d, Remaining = %d\n", i, h[i].original, h[i].size);
}

void firstFit(struct Hole h[], int nh, struct Process p[], int np) {
    for (int i = 0; i < np; i++) {
        p[i].allocatedHole = -1;
        for (int j = 0; j < nh; j++) {
            if (h[j].size >= p[i].size) {
                p[i].allocatedHole = j;
                h[j].size -= p[i].size;
                break;
            }
        }
    }
    printResult(p, np, h, nh, "First Fit");
}

void bestFit(struct Hole h[], int nh, struct Process p[], int np) {
    // Sort holes by size (ascending)
    for (int i = 0; i < nh - 1; i++) {
        for (int j = i + 1; j < nh; j++) {
            if (h[j].size < h[i].size) {
                struct Hole temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }
        }
    }

    for (int i = 0; i < np; i++) {
        p[i].allocatedHole = -1;
        for (int j = 0; j < nh; j++) {
            if (h[j].size >= p[i].size) {
                p[i].allocatedHole = h[j].id;
                h[j].size -= p[i].size;
                break;
            }
        }
    }
    printResult(p, np, h, nh, "Best Fit");
}

int main() {
    int nh = 3, np = 4;
    
    struct Hole holes[MAX] = {{100, 100, 0}, {500, 500, 1}, {200, 200, 2}};
    struct Process processes[MAX] = {{212, -1}, {417, -1}, {112, -1}, {426, -1}};

    // First Fit
    resetHoles(holes, nh);
    firstFit(holes, nh, processes, np);

    // Best Fit
    struct Hole bestFitHoles[MAX] = {{100, 100, 0}, {500, 500, 1}, {200, 200, 2}};
    resetHoles(bestFitHoles, nh);
    bestFit(bestFitHoles, nh, processes, np);

    return 0;
}
