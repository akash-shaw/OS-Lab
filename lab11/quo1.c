#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int absDiff(int a, int b) {
    return abs(a - b);
}

void printSeq(int *seq, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", seq[i]);
    printf("\n");
}

int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void sstf(int *req, int n, int head) {
    int *done = calloc(n, sizeof(int));
    int total = 0;
    printf("SSTF Order: ");
    for (int i = 0; i < n; i++) {
        int min = 1e9, idx = -1;
        for (int j = 0; j < n; j++) {
            if (!done[j] && absDiff(head, req[j]) < min) {
                min = absDiff(head, req[j]);
                idx = j;
            }
        }
        total += absDiff(head, req[idx]);
        head = req[idx];
        done[idx] = 1;
        printf("%d ", head);
    }
    printf("\nTotal head movement: %d\n", total);
    free(done);
}

void scan(int *req, int n, int head, int size) {
    int total = 0;
    req[n++] = head;
    qsort(req, n, sizeof(int), compare);
    int pos;
    for (pos = 0; pos < n; pos++) if (req[pos] == head) break;

    printf("SCAN Order: ");
    for (int i = pos; i < n; i++) {
        printf("%d ", req[i]);
        if (i > pos) total += absDiff(req[i], req[i - 1]);
    }
    total += absDiff(req[n - 1], size - 1);
    printf("%d ", size - 1);

    for (int i = pos - 1; i >= 0; i--) {
        total += absDiff(req[i + 1], req[i]);
        printf("%d ", req[i]);
    }
    printf("\nTotal head movement: %d\n", total);
}

void cscan(int *req, int n, int head, int size) {
    int total = 0;
    req[n++] = head;
    qsort(req, n, sizeof(int), compare);
    int pos;
    for (pos = 0; pos < n; pos++) if (req[pos] == head) break;

    printf("C-SCAN Order: ");
    for (int i = pos; i < n; i++) {
        printf("%d ", req[i]);
        if (i > pos) total += absDiff(req[i], req[i - 1]);
    }
    total += absDiff(req[n - 1], size - 1);
    printf("%d ", size - 1);
    total += size - 1;

    for (int i = 0; i < pos; i++) {
        if (i > 0) total += absDiff(req[i], req[i - 1]);
        else total += req[i];
        printf("%d ", req[i]);
    }
    printf("\nTotal head movement: %d\n", total);
}

void clook(int *req, int n, int head) {
    int total = 0;
    req[n++] = head;
    qsort(req, n, sizeof(int), compare);
    int pos;
    for (pos = 0; pos < n; pos++) if (req[pos] == head) break;

    printf("C-LOOK Order: ");
    for (int i = pos; i < n; i++) {
        printf("%d ", req[i]);
        if (i > pos) total += absDiff(req[i], req[i - 1]);
    }

    total += absDiff(req[n - 1], req[0]);

    for (int i = 0; i < pos; i++) {
        if (i > 0) total += absDiff(req[i], req[i - 1]);
        else total += absDiff(req[i], req[n - 1]);
        printf("%d ", req[i]);
    }
    printf("\nTotal head movement: %d\n", total);
}

int main() {
    int *requests;
    int n = 8, head = 50, disk_size = 200;
    requests = (int *)malloc(n * sizeof(int));

    // Hardcoded input
    int test[] = {98, 183, 37, 122, 14, 124, 65, 67};
    for (int i = 0; i < n; i++) requests[i] = test[i];

    int choice;
    do {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: sstf(requests, n, head); break;
            case 2: scan(requests, n, head, disk_size); break;
            case 3: cscan(requests, n, head, disk_size); break;
            case 4: clook(requests, n, head); break;
            case 5: break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 5);

    free(requests);
    return 0;
}
