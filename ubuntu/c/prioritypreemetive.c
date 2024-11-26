#include <stdio.h>
#include <limits.h>

#define MAX 20

typedef struct {
    int pid;       // Process ID
    int arrival;   // Arrival Time
    int burst;     // Burst Time
    int priority;  // Priority
    int finish;    // Finish Time
    int waiting;   // Waiting Time
    int total;     // Turnaround Time
    int remaining; // Remaining Burst Time
} Process;

// Function to calculate the times and Gantt chart
void calculateTimes(Process processes[], int n, int ganttChart[], int *ganttSize) {
    int currentTime = 0, completed = 0, minPriority, selectedProcess;
    *ganttSize = 0;

    while (completed < n) {
        minPriority = INT_MAX;
        selectedProcess = -1;

        // Find the process with the highest priority (lowest priority value)
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0 && processes[i].priority < minPriority) {
                minPriority = processes[i].priority;
                selectedProcess = i;
            }
        }

        if (selectedProcess == -1) {
            // No process available, increment time
            currentTime++;
            continue;
        }

        // Execute the selected process for 1 unit of time
        ganttChart[(*ganttSize)++] = processes[selectedProcess].pid;
        currentTime++;
        processes[selectedProcess].remaining--;

        // If the process finishes execution
        if (processes[selectedProcess].remaining == 0) {
            processes[selectedProcess].finish = currentTime;
            processes[selectedProcess].total = processes[selectedProcess].finish - processes[selectedProcess].arrival;
            processes[selectedProcess].waiting = processes[selectedProcess].total - processes[selectedProcess].burst;
            completed++;
        }
    }
}

// Function to print the process table
void printTable(Process processes[], int n) {
    printf("\n%-12s %-13s %-11s %-10s %-12s %-10s %-12s\n", 
           "Process_ID", "Arrival_Time", "Burst_Time", "Priority", "Finish_Time", "Total_Time", "Waiting_Time");

    for (int i = 0; i < n; i++) {
        printf("P%-11d %-13d %-11d %-10d %-12d %-10d %-12d\n",
               processes[i].pid, processes[i].arrival, processes[i].burst, processes[i].priority,
               processes[i].finish, processes[i].total, processes[i].waiting);
    }
}

// Function to print the Gantt chart
void printGanttChart(int ganttChart[], int ganttSize) {
    printf("\nGantt Chart:\n");

    // Print process bars
    printf("|");
    for (int i = 0; i < ganttSize; i++) {
        printf(" P%d |", ganttChart[i]);
    }
    printf("\n");

    // Print time labels
    printf("0");
    for (int i = 1; i <= ganttSize; i++) {
        printf("    %d", i);
    }
    printf("\n");
}

int main() {
    int n;
    Process processes[MAX];
    int ganttChart[100];
    int ganttSize;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority of process P%d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].remaining = processes[i].burst; // Initialize remaining burst time
    }

    calculateTimes(processes, n, ganttChart, &ganttSize);
    printTable(processes, n);
    printGanttChart(ganttChart, ganttSize);

    return 0;
}
