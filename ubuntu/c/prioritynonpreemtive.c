#include <stdio.h>

typedef struct {
    int pid;              // Process ID
    int arrivalTime;      // Arrival Time
    int burstTime;        // Burst Time
    int finishTime;       // Finish Time
    int waitingTime;      // Waiting Time
    int turnaroundTime;   // Turnaround Time
    int priority;         // Priority
} Process;

// Function to sort processes by priority (and arrival time if needed for stability)
void sortByPriority(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate finish, turnaround, and waiting times
void calculateTimes(Process proc[], int n) {
    proc[0].finishTime = proc[0].arrivalTime + proc[0].burstTime;
    proc[0].turnaroundTime = proc[0].finishTime - proc[0].arrivalTime;
    proc[0].waitingTime = proc[0].turnaroundTime - proc[0].burstTime;

    for (int i = 1; i < n; i++) {
        if (proc[i].arrivalTime > proc[i - 1].finishTime) {
            proc[i].finishTime = proc[i].arrivalTime + proc[i].burstTime;
        } else {
            proc[i].finishTime = proc[i - 1].finishTime + proc[i].burstTime;
        }
        proc[i].turnaroundTime = proc[i].finishTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
    }
}

// Function to print the Gantt Chart
void printGanttChart(Process proc[], int n) {
    printf("\nGantt Chart:\n");
    printf("|");

    for (int i = 0; i < n; i++) {
        printf("  P%d  |", proc[i].pid);
    }

    printf("\n%d", proc[0].arrivalTime);
    for (int i = 0; i < n; i++) {
        printf("      %d", proc[i].finishTime);
    }
    printf("\n");
}

// Function to display the process details
void printProcesses(Process proc[], int n) {
    printf("\nPID\tArrival\tBurst\tPriority\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].arrivalTime,
               proc[i].burstTime,
               proc[i].priority,
               proc[i].finishTime,
               proc[i].turnaroundTime,
               proc[i].waitingTime);
    }
}

// Main function
int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
    }

    // Sort processes by priority
    sortByPriority(proc, n);

    // Calculate times
    calculateTimes(proc, n);

    // Print process details and Gantt Chart
    printProcesses(proc, n);
    printGanttChart(proc, n);

    return 0;
}
