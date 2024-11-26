#include <stdio.h>

int main() {
    int n, m, i, j, k;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Initialize matrices and arrays
    int alloc[n][m]; // Allocation Matrix
    int max[n][m];   // Maximum Matrix
    int avail[m];    // Available Resources

    // Input Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("Enter the Available Resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Initialize finish flags to 0 (unfinished) and arrays
    int f[n], ans[n], ind = 0;
    for (i = 0; i < n; i++) {
        f[i] = 0;
    }

    // Need Matrix calculation
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Banker's algorithm for safe sequence
    int y = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i; // Add to the safe sequence
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y]; // Update available resources
                    }
                    f[i] = 1; // Mark the process as finished
                }
            }
        }
    }

    // Checking if all processes were finished (safe state)
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The following system is not safe\n");
            break;
        }
    }

    // If the system is safe, print the safe sequence
    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++) {
            printf(" P%d ->", ans[i]);
        }
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}
