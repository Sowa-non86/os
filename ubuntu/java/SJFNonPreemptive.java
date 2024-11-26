import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Process {
    int pid, arrivalTime, burstTime, startTime, finishTime, waitingTime, turnaroundTime;
    boolean completed;

    public Process(int pid, int arrivalTime, int burstTime) {
        this.pid = pid;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.completed = false;
    }
}

class GanttChartEntry {
    int pid, startTime, endTime;

    public GanttChartEntry(int pid, int startTime, int endTime) {
        this.pid = pid;
        this.startTime = startTime;
        this.endTime = endTime;
    }
}

public class SJFNonPreemptive {

    public static void findTimes(Process[] processes, int n, List<GanttChartEntry> ganttChart) {
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
                ganttChart.add(new GanttChartEntry(processes[minIndex].pid, processes[minIndex].startTime, processes[minIndex].finishTime));

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

    public static void displayGanttChart(List<GanttChartEntry> ganttChart) {
        System.out.println("\nGantt Chart:");
        for (GanttChartEntry entry : ganttChart) {
            System.out.print("| P" + entry.pid + " ");
        }
        System.out.println("|");

        for (GanttChartEntry entry : ganttChart) {
            System.out.print(entry.startTime + "\t");
        }
        System.out.println(ganttChart.get(ganttChart.size() - 1).endTime);
    }

    public static void SJF_NonPreemptive(Process[] processes, int n) {
        List<GanttChartEntry> ganttChart = new ArrayList<>();
        findTimes(processes, n, ganttChart);

        System.out.println("\nPID\tArrival\tBurst\tStart\tFinish\tTurnaround\tWaiting");
        for (Process p : processes) {
            System.out.printf("%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
                    p.pid, p.arrivalTime, p.burstTime, p.startTime, p.finishTime, p.turnaroundTime, p.waitingTime);
        }

        displayGanttChart(ganttChart);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter number of processes: ");
        int n = scanner.nextInt();

        Process[] processes = new Process[n];
        for (int i = 0; i < n; i++) {
            System.out.printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
            int arrivalTime = scanner.nextInt();
            int burstTime = scanner.nextInt();
            processes[i] = new Process(i + 1, arrivalTime, burstTime);
        }

        SJF_NonPreemptive(processes, n);

        scanner.close();
    }
}
