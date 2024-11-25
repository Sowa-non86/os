#include <stdio.h>

int findOPT(int frames[], int pages[], int num_frames, int num_pages, int current) {
    int farthest = current, pos = -1, i, j;

    for (i = 0; i < num_frames; i++) {
        int found = 0;
        for (j = current + 1; j < num_pages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }
        if (!found) {  // If a page is not used in the future
            return i;
        }
    }

    return (pos == -1) ? 0 : pos;  // Default to the first frame if no farthest found
}

int main() {
    int frames[10], pages[30], num_frames, num_pages, i, j, pos, page_faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter page reference string: ");
    for (i = 0; i < num_pages; i++)
        scanf("%d", &pages[i]);

    for (i = 0; i < num_frames; i++)
        frames[i] = -1;  // Initialize frames as empty

    printf("\nPage Reference | Frames");
    printf("\n---------------|------------------");

    for (i = 0; i < num_pages; i++) {
        int found = 0;

        // Check if the page is already in the frame
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {  // Page fault occurs
            if (i < num_frames) {
                pos = i;  // First empty frame
            } else {
                pos = findOPT(frames, pages, num_frames, num_pages, i);
            }
            frames[pos] = pages[i];
            page_faults++;
        }

        // Print the table row
        printf("\n%12d |", pages[i]);
        for (j = 0; j < num_frames; j++) {
            if (frames[j] != -1)
                printf(" %d", frames[j]);
            else
                printf(" -");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", page_faults);
    return 0;
}
