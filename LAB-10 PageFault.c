#include <stdio.h>
#include <stdlib.h>

void printFrames(int frames[], int n, const char* msg) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("%s\n", msg);
}

void fifo(int pages[], int n, int frames[], int frameCount) {
    int front = 0, faults = 0;
    printf("The Page Replacement Process for FIFO is:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % frameCount;
            faults++;
            char msg[20];
            snprintf(msg, sizeof(msg), "PF No. %d", faults);
            printFrames(frames, frameCount, msg);
        } else {
            printFrames(frames, frameCount, "");
        }
    }
    printf("The number of Page Faults using FIFO are %d\n", faults);
}

void lru(int pages[], int n, int frames[], int frameCount) {
    int time[frameCount], faults = 0, counter = 0;
    printf("The Page Replacement Process for LRU is:\n");
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        time[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0, least = counter;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = counter++;
                break;
            }
            if (time[j] < least) {
                least = time[j];
            }
        }

        if (!found) {
            int replace = 0;
            for (int j = 0; j < frameCount; j++) {
                if (time[j] == least) {
                    replace = j;
                    break;
                }
            }
            frames[replace] = pages[i];
            time[replace] = counter++;
            faults++;
            char msg[20];
            snprintf(msg, sizeof(msg), "PF No. %d", faults);
            printFrames(frames, frameCount, msg);
        } else {
            printFrames(frames, frameCount, "");
        }
    }
    printf("The number of Page Faults using LRU are %d\n", faults);
}

void optimal(int pages[], int n, int frames[], int frameCount) {
    int faults = 0;
    printf("The Page Replacement Process for Optimal is:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int replace = -1, farthest = i;
            for (int j = 0; j < frameCount; j++) {
                int nextUse = n;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }
                if (nextUse > farthest) {
                    farthest = nextUse;
                    replace = j;
                }
            }
            if (replace == -1) {
                replace = 0;
            }
            frames[replace] = pages[i];
            faults++;
            char msg[20];
            snprintf(msg, sizeof(msg), "PF No. %d", faults);
            printFrames(frames, frameCount, msg);
        } else {
            printFrames(frames, frameCount, "");
        }
    }
    printf("The number of Page Faults using Optimal are %d\n", faults);
}

int main() {
    int n, frameCount;

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n], frames[frameCount];

    printf("Enter page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("\nFIFO:\n");
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }
    fifo(pages, n, frames, frameCount);

    printf("\nLRU:\n");
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }
    lru(pages, n, frames, frameCount);

    printf("\nOptimal:\n");
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }
    optimal(pages, n, frames, frameCount);

    return 0;
}
