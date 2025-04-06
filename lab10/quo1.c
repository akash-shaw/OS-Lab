#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1

void printFrames(int frames[], int nf) {
    for (int i = 0; i < nf; i++)
        if (frames[i] != EMPTY) printf("%d ", frames[i]);
        else printf("- ");
    printf("\n");
}

int isPresent(int frames[], int nf, int page) {
    for (int i = 0; i < nf; i++)
        if (frames[i] == page) return 1;
    return 0;
}

void fifo(int pages[], int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int faults = 0, index = 0;

    for (int i = 0; i < nf; i++) frames[i] = EMPTY;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < np; i++) {
        if (!isPresent(frames, nf, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % nf;
            faults++;
        }
        printFrames(frames, nf);
    }

    printf("Total Page Faults (FIFO): %d\n", faults);
    free(frames);
}

int predict(int pages[], int np, int frames[], int nf, int index) {
    int farthest = index, pos = -1;

    for (int i = 0; i < nf; i++) {
        int j;
        for (j = index; j < np; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == np) return i; // Never used again
    }
    return (pos == -1) ? 0 : pos;
}

void optimal(int pages[], int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int faults = 0, count = 0;

    for (int i = 0; i < nf; i++) frames[i] = EMPTY;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < np; i++) {
        if (!isPresent(frames, nf, pages[i])) {
            if (count < nf)
                frames[count++] = pages[i];
            else {
                int pos = predict(pages, np, frames, nf, i + 1);
                frames[pos] = pages[i];
            }
            faults++;
        }
        printFrames(frames, nf);
    }

    printf("Total Page Faults (Optimal): %d\n", faults);
    free(frames);
}

int main() {
    // Hardcoded input for simplicity
    int nf = 3; // number of frames
    int np = 12; // number of pages
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};

    printf("Number of Frames: %d\n", nf);
    printf("Page Reference String: ");
    for (int i = 0; i < np; i++) printf("%d ", pages[i]);
    printf("\n");

    fifo(pages, np, nf);
    optimal(pages, np, nf);

    return 0;
}
