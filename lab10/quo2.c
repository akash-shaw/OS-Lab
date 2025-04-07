#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1

int isPresent(int frames[], int nf, int page) {
    for (int i = 0; i < nf; i++)
        if (frames[i] == page) return i;
    return -1;
}

void printFrames(int frames[], int nf) {
    for (int i = 0; i < nf; i++)
        if (frames[i] != EMPTY) printf("%d ", frames[i]);
        else printf("- ");
    printf("\n");
}

void lru(int pages[], int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int *recent = (int *)malloc(nf * sizeof(int));
    int time = 0, faults = 0;

    for (int i = 0; i < nf; i++) {
        frames[i] = EMPTY;
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < np; i++) {
        int page = pages[i];
        int idx = isPresent(frames, nf, page);

        if (idx == -1) { 
            int lruIndex = 0;
            for (int j = 1; j < nf; j++)
                if (recent[j] < recent[lruIndex]) lruIndex = j;

            frames[lruIndex] = page;
            recent[lruIndex] = time;
            faults++;
        } else {
            recent[idx] = time;
        }

        time++;
        printFrames(frames, nf);
    }

    printf("Total Page Faults (LRU): %d\n", faults);

    free(frames);
    free(recent);
}

int main() {
    int nf;
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3}; 
    int np = sizeof(pages) / sizeof(pages[0]);

    printf("Enter number of frames: ");
    scanf("%d", &nf);

    printf("Page Reference String: ");
    for (int i = 0; i < np; i++) printf("%d ", pages[i]);
    printf("\n");

    lru(pages, np, nf);
    return 0;
}
