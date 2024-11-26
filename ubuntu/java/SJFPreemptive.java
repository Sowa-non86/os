import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Process {
    int pid, arrivalTime, burstTime, remainingTime, finishTime, waitingTime, turnaroundTime, startTime;

    public Process(int pid, int arrivalTime, int burstTime) {
        this.pid = pid;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.remainingTime = burstTime;
        this.startTime = -1; // Indicates the process hasn't started yet
    }
}

class GanttChart {
    int pid, startTime, endTime;

    public GanttChart(int pid, int startTime) {
        this.pid = pid;
        this.startTime = startTime;
    }

    public void setEndTime(int endTime) {
        this.endTime = endTime;
    }
}

public class SJFPreemptive {
    public static void sjfPreemptive(Process[] proc, int n) {
        int completed = 0, currentTime = 0;
        int totalBurstTime = 0;
        List<GanttChart> ganttChart = new ArrayList<>();

        // Calculate total burst time
        for (Process process : proc) {
            totalBurstTime += process.burstTime;
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
                Process currentProc = proc[minIndex];
                if (currentProc.startTime == -1) {
                    currentProc.startTime = currentTime;
                }

                // Add a Gantt chart entry if the process changes
                if (ganttChart.isEmpty() || ganttChart.get(ganttChart.size() - 1).pid != currentProc.pid) {
                    if (!ganttChart.isEmpty()) {
                        ganttChart.get(ganttChart.size() - 1).setEndTime(currentTime);
                    }
                    ganttChart.add(new GanttChart(currentProc.pid, currentTime));
                }

                // Process execution
                currentTime++;
                currentProc.remainingTime--;

                if (currentProc.remainingTime == 0) {
                    currentProc.finishTime = currentTime;
                    currentProc.turnaroundTime = currentProc.finishTime - currentProc.arrivalTime;
                    currentProc.waitingTime = currentProc.turnaroundTime - currentProc.burstTime;
                    completed++;
                }
            } else {
                currentTime++; // Increment time if no process is ready
            }
        }

        // Update the end time of the last Gantt chart entry
        if (!ganttChart.isEmpty()) {
            ganttChart.get(ganttChart.size() - 1).setEndTime(currentTime);
        }

        // Print process details
        System.out.println("\nPID\tArrival\tBurst\tFinish\tTurnaround\tWaiting");
        for (Process process : proc) {
            System.out.printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", process.pid, process.arrivalTime,
                    process.burstTime, process.finishTime, process.turnaroundTime, process.waitingTime);
        }

        // Print Gantt chart
        printGanttChart(ganttChart);
    }

    public static void printGanttChart(List<GanttChart> ganttChart) {
        System.out.println("\nGantt Chart:");
        System.out.print("|");

        // Print process IDs
        for (GanttChart entry : ganttChart) {
            System.out.printf("  P%d  |", entry.pid);
        }
        System.out.println();

        // Print time intervals
        for (GanttChart entry : ganttChart) {
            System.out.printf("%-6d", entry.startTime);
        }
        System.out.printf("%d\n", ganttChart.get(ganttChart.size() - 1).endTime);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter number of processes: ");
        int n = scanner.nextInt();
        Process[] proc = new Process[n];

        for (int i = 0; i < n; i++) {
            System.out.printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
            int arrivalTime = scanner.nextInt();
            int burstTime = scanner.nextInt();
            proc[i] = new Process(i + 1, arrivalTime, burstTime);
        }

        sjfPreemptive(proc, n);
    }
}
