Not enough storage … Your Google One storage subscription was canceled because your payment method failed
FIFO_LRU_OPT.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

int pages[MAX_PAGES];
int frames[MAX_FRAMES];
int counter[MAX_FRAMES];
int page_faults = 0;
int page_hits = 0;

void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }
}

void displayFrames(int n) {
    printf("Frames: ");
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

int findLRU(int n) {
    int min = counter[0], idx = 0;
    for (int i = 1; i < n; i++) {
        if (counter[i] < min) {
            min = counter[i];
            idx = i;
        }
    }
    return idx;
}

void fifo(int num_frames, int num_pages) {
    initialize();
    int frame_index = 0;

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                page_hits++;
                break;
            }
        }

        if (!found) {
            frames[frame_index] = page;
            frame_index = (frame_index + 1) % num_frames;
            page_faults++;
        }

        displayFrames(num_frames);
    }
}

void lru(int num_frames, int num_pages) {
    initialize();

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                counter[j] = i;
                page_hits++;
                break;
            }
        }

        if (!found) {
            int idx = findLRU(num_frames);
            frames[idx] = page;
            counter[idx] = i;
            page_faults++;
        }

        displayFrames(num_frames);
    }
}

void optimal(int num_frames, int num_pages) {
    initialize();

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                page_hits++;
                break;
            }
        }

        if (!found) {
            int farthest = i;
            int replace_idx = -1;
            for (int j = 0; j < num_frames; j++) {
                int k;
                for (k = i + 1; k < num_pages; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace_idx = j;
                        }
                        break;
                    }
                }
                if (k == num_pages) {
                    replace_idx = j;
                    break;
                }
            }

            if (replace_idx != -1) {
                frames[replace_idx] = page;
                page_faults++;
            }
        }

        displayFrames(num_frames);
    }
}

int main() {
    int num_pages, num_frames, choice;
    float hit_ratio;
    float fault_ratio;

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    do {
        printf("\nPage Replacement Algorithms:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(num_frames, num_pages);
                hit_ratio = (float) page_hits / num_pages;
                fault_ratio = (float) page_faults / num_pages;

                printf("\nResults:\n");
                printf("Number of Faults: %d\n", page_faults);
                printf("Number of Hits: %d\n", page_hits);
                printf("Hit Ratio: %.2f\n", hit_ratio);
                printf("Fault Ratio: %.2f\n", fault_ratio);
                break;
            case 2:
                lru(num_frames, num_pages);
                hit_ratio = (float) page_hits / num_pages;
                fault_ratio = (float) page_faults / num_pages;

                printf("\nResults:\n");
                printf("Number of Faults: %d\n", page_faults);
                printf("Number of Hits: %d\n", page_hits);
                printf("Hit Ratio: %.2f\n", hit_ratio);
                printf("Fault Ratio: %.2f\n", fault_ratio);
                break;
            case 3:
                optimal(num_frames, num_pages);
                hit_ratio = (float) page_hits / num_pages;
                fault_ratio = (float) page_faults / num_pages;

                printf("\nResults:\n");
                printf("Number of Faults: %d\n", page_faults);
                printf("Number of Hits: %d\n", page_hits);
                printf("Hit Ratio: %.2f\n", hit_ratio);
                printf("Fault Ratio: %.2f\n", fault_ratio);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}