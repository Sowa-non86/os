#include <stdio.h>

int main() {
    int frames[10], pages[30], num_frames, num_pages, i, j, k, page_faults = 0;
    int oldest = 0;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter page reference string: ");
    for (i = 0; i < num_pages; i++)
        scanf("%d", &pages[i]);

    for (i = 0; i < num_frames; i++)
        frames[i] = -1;  // initialize frames as empty

    printf("\nPage Reference | Frames");
    printf("\n---------------|------------------");

    for (i = 0; i < num_pages; i++) {
        int found = 0;
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {  // page fault
            frames[oldest] = pages[i];
            oldest = (oldest + 1) % num_frames;
            page_faults++;
        }

        printf("\n%12d |", pages[i]);
        for (k = 0; k < num_frames; k++) {
            if (frames[k] != -1)
                printf(" %d", frames[k]);
            else
                printf(" -");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", page_faults);
    return 0;
}
