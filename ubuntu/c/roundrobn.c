#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a process
typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
} Process;

// Function to perform Round Robin scheduling
void roundRobin(Process* processes, int numProcesses, int quantum, int** ganttChart, int* ganttSize) {
    int time = 0;
    int front = 0, rear = 0;
    int queue[numProcesses];
    bool inQueue[numProcesses];

    *ganttChart = (int*)malloc(numProcesses * 3 * sizeof(int)); // To store Gantt chart entries
    *ganttSize = 0;

    // Initialize processes and queue
    for (int i = 0; i < numProcesses; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        inQueue[i] = false;
    }

    // Sort processes by arrival time
    for (int i = 0; i < numProcesses - 1; i++) {
        for (int j = i + 1; j < numProcesses; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Enqueue the first process
    queue[rear++] = 0;
    inQueue[0] = true;

    while (front < rear) {
        int current = queue[front++];
        Process* process = &processes[current];

        if (process->remainingTime > quantum) {
            (*ganttChart)[(*ganttSize)++] = process->pid;
            (*ganttChart)[(*ganttSize)++] = time;
            (*ganttChart)[(*ganttSize)++] = time + quantum;

            time += quantum;
            process->remainingTime -= quantum;
        } else {
            (*ganttChart)[(*ganttSize)++] = process->pid;
            (*ganttChart)[(*ganttSize)++] = time;
            (*ganttChart)[(*ganttSize)++] = time + process->remainingTime;

            time += process->remainingTime;
            process->remainingTime = 0;
            process->completionTime = time;
            process->turnaroundTime = process->completionTime - process->arrivalTime;
            process->waitingTime = process->turnaroundTime - process->burstTime;
        }

        // Add new processes to the queue based on the current time
        for (int i = 0; i < numProcesses; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= time && processes[i].remainingTime > 0) {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }

        // Re-add the current process to the queue if it still has remaining time
        if (process->remainingTime > 0) {
            queue[rear++] = current;
        }
    }
}

// Function to display waiting time and turnaround time
void displayTimes(Process* processes, int numProcesses) {
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].waitingTime, 
               processes[i].turnaroundTime);
    }
}

// Function to print the Gantt chart
void printGanttChart(int* ganttChart, int ganttSize) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttSize; i += 3) {
        printf("| P%d ", ganttChart[i]);
    }
    printf("|\n");

    for (int i = 0; i < ganttSize; i += 3) {
        printf("%d\t", ganttChart[i + 1]);
    }
    printf("%d\n", ganttChart[ganttSize - 1]);
}

int main() {
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    Process* processes = (Process*)malloc(numProcesses * sizeof(Process));

    for (int i = 0; i < numProcesses; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    int quantum;
    printf("Enter the Time Quantum for Round Robin: ");
    scanf("%d", &quantum);

    printf("\nPreset Processes:\n");
    printf("PID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime);
    }

    printf("\n--- Round Robin ---\n");

    int* ganttChart;
    int ganttSize;
    roundRobin(processes, numProcesses, quantum, &ganttChart, &ganttSize);

    displayTimes(processes, numProcesses);
    printGanttChart(ganttChart, ganttSize);

    free(processes);
    free(ganttChart);
    return 0;
}