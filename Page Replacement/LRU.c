#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames[10], pages[30], time[10];
    int num_frames, num_pages, i, j, pos, page_faults = 0, counter = 0;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter page reference string: ");
    for (i = 0; i < num_pages; i++)
        scanf("%d", &pages[i]);

    for (i = 0; i < num_frames; i++) {
        frames[i] = -1;  // initialize frames as empty
        time[i] = 0;     // initialize time array
    }

    printf("\nPage Reference | Frames");
    printf("\n---------------|------------------");

    for (i = 0; i < num_pages; i++) {
        int found = 0;

        // Check if the page is already in the frame
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;  // Update usage time
                break;
            }
        }

        if (!found) {  // Page fault occurs
            if (frames[j] == -1) {
                pos = j;  // First empty frame
            } else {
                pos = findLRU(time, num_frames);  // Find the least recently used
            }
            frames[pos] = pages[i];
            time[pos] = ++counter;
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
