#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
    int startTime;
} Process;

typedef struct {
    int pid;
    int startTime;
    int endTime;
} GanttChart;

void sjfPreemptive(Process proc[], int n) {
    int completed = 0, currentTime = 0;
    int totalBurstTime = 0;
    GanttChart ganttChart[100];  // Assuming no more than 100 entries in the Gantt Chart
    int ganttSize = 0;

    // Calculate total burst time
    for (int i = 0; i < n; i++) {
        totalBurstTime += proc[i].burstTime;
    }

    while (completed != n) {
        int minIndex = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0) {
                if (minIndex == -1 || proc[i].remainingTime < proc[minIndex].remainingTime) {
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1) {
            Process *currentProc = &proc[minIndex];
            if (currentProc->startTime == -1) {
                currentProc->startTime = currentTime;
            }

            // Add a Gantt chart entry if the process changes
            if (ganttSize == 0 || ganttChart[ganttSize - 1].pid != currentProc->pid) {
                if (ganttSize > 0) {
                    ganttChart[ganttSize - 1].endTime = currentTime;
                }
                ganttChart[ganttSize].pid = currentProc->pid;
                ganttChart[ganttSize].startTime = currentTime;
                ganttSize++;
            }

            // Process execution
            currentTime++;
            currentProc->remainingTime--;

            if (currentProc->remainingTime == 0) {
                currentProc->finishTime = currentTime;
                currentProc->turnaroundTime = currentProc->finishTime - currentProc->arrivalTime;
                currentProc->waitingTime = currentProc->turnaroundTime - currentProc->burstTime;
                completed++;
            }
        } else {
            currentTime++; // Increment time if no process is ready
        }
    }

    // Update the end time of the last Gantt chart entry
    if (ganttSize > 0) {
        ganttChart[ganttSize - 1].endTime = currentTime;
    }

    // Print process details
    printf("\nPID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime,
                proc[i].burstTime, proc[i].finishTime, proc[i].turnaroundTime, proc[i].waitingTime);
    }

    // Print Gantt chart
    printGanttChart(ganttChart, ganttSize);
}

void printGanttChart(GanttChart ganttChart[], int ganttSize) {
    printf("\nGantt Chart:\n");
    printf("|");

    // Print process IDs
    for (int i = 0; i < ganttSize; i++) {
        printf("  P%d  |", ganttChart[i].pid);
    }
    printf("\n");

    // Print time intervals
    for (int i = 0; i < ganttSize; i++) {
        printf("%-6d", ganttChart[i].startTime);
    }
    printf("%d\n", ganttChart[ganttSize - 1].endTime);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].pid = i + 1;
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].startTime = -1; // Process has not started yet
    }

    sjfPreemptive(proc, n);

    return 0;
}
