#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;             // Process ID
    int arrivalTime;     // Arrival Time
    int burstTime;       // Burst Time
    int completionTime;  // Completion Time
    int turnaroundTime;  // Turnaround Time
    int waitingTime;     // Waiting Time
} Process;

// Function to compare processes by arrival time (for sorting)
int compareByArrivalTime(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrivalTime - p2->arrivalTime;
}

// Function to calculate completion, turnaround, and waiting times
void calculateTimes(Process processes[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrivalTime) {
            time = processes[i].arrivalTime;
        }
        time += processes[i].burstTime;
        processes[i].completionTime = time;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

// Function to print the process table
void printProcessTable(Process processes[], int n) {
    printf("\n\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

// Function to print the Gantt Chart
void printGanttChart(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i].pid);
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++) {
        printf("   %d", processes[i].completionTime);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i + 1; // Assign Process ID
    }

    // Sort processes by arrival time
    qsort(processes, n, sizeof(Process), compareByArrivalTime);

    // Calculate times
    calculateTimes(processes, n);

    // Print process table and Gantt chart
    printProcessTable(processes, n);
    printGanttChart(processes, n);

    // Calculate and print total turnaround and waiting times
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("\nTotal Turnaround Time: %d\n", totalTurnaroundTime);
    printf("Total Waiting Time: %d\n", totalWaitingTime);

    return 0;
}
