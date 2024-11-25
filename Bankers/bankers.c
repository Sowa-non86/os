#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int checkSafeState() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSeq[MAX_PROCESSES];
    int count = 0;

    // Initialize work[] to available[]
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    // Find a safe sequence
    while (count < MAX_PROCESSES) 
    {
        int found = 0;
        for (int p = 0; p < MAX_PROCESSES; p++) 
        {
            if (!finish[p]) {
                int canAllocate = 1;

                for (int r = 0; r < MAX_RESOURCES; r++) 
                {
                    if (need[p][r] > work[r]) {
                        canAllocate = 0;
                        break;
                    }
                }
                
                if (canAllocate) 
                {
                    for (int r = 0; r < MAX_RESOURCES; r++) 
                    {
                        work[r] += allocation[p][r];
                    }
                    finish[p] = 1;
                    safeSeq[count++] = p;
                    found = 1;
                    break;
                }
            }
        }

        if (!found) {
            return 0; // No safe sequence found, system is in a deadlock state
        }
    }

    // Print the safe sequence
    printf("Safe Sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 1; // System is in a safe state
}

void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int main() {
    // Initialize available resources
    printf("Enter available resources: ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize maximum resources for each process
    printf("Enter maximum resource matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    // Initialize allocated resources for each process
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the need matrix
    calculateNeed();

    // Check if the system is in a safe state
    if (checkSafeState()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is in a deadlock state.\n");
    }

    return 0;
}
