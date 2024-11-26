#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int startTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
    bool completed;
} Process;

typedef struct {
    int pid;
    int startTime;
    int endTime;
} GanttChartEntry;

void findTimes(Process processes[], int n, GanttChartEntry ganttChart[], int *ganttSize) {
    int completed = 0, currentTime = 0;
    while (completed != n) {
        int minIndex = -1;

        // Find the process with the shortest burst time among available processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].completed) {
                if (minIndex == -1 || processes[i].burstTime < processes[minIndex].burstTime) {
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1) {
            if (currentTime < processes[minIndex].arrivalTime) {
                currentTime = processes[minIndex].arrivalTime; // Account for idle time
            }

            // Set start time
            processes[minIndex].startTime = currentTime;

            // Update current time and finish time
            currentTime += processes[minIndex].burstTime;
            processes[minIndex].finishTime = currentTime;

            // Add to Gantt chart
            ganttChart[*ganttSize].pid = processes[minIndex].pid;
            ganttChart[*ganttSize].startTime = processes[minIndex].startTime;
            ganttChart[*ganttSize].endTime = processes[minIndex].finishTime;
            (*ganttSize)++;

            // Calculate turnaround and waiting times
            processes[minIndex].turnaroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnaroundTime - processes[minIndex].burstTime;

            // Mark process as completed
            processes[minIndex].completed = true;
            completed++;
        } else {
            currentTime++; // Increment time for idle period
        }
    }
}

void displayGanttChart(GanttChartEntry ganttChart[], int ganttSize) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttSize; i++) {
        printf("| P%d ", ganttChart[i].pid);
    }
    printf("|\n");

    for (int i = 0; i < ganttSize; i++) {
        printf("%d\t", ganttChart[i].startTime);
    }
    printf("%d\n", ganttChart[ganttSize - 1].endTime);
}

void SJF_NonPreemptive(Process processes[], int n) {
    GanttChartEntry ganttChart[100];  // Assuming a maximum of 100 entries in Gantt Chart
    int ganttSize = 0;

    findTimes(processes, n, ganttChart, &ganttSize);

    printf("\nPID\tArrival\tBurst\tStart\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n", 
            processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, 
            processes[i].startTime, processes[i].finishTime, 
            processes[i].turnaroundTime, processes[i].waitingTime);
    }

    displayGanttChart(ganttChart, ganttSize);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].pid = i + 1;
        processes[i].completed = false;
    }

    SJF_NonPreemptive(processes, n);

    return 0;
}
