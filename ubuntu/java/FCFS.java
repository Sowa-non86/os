import java.util.Scanner;
import java.util.Arrays;

class Process implements Comparable<Process> {
    int pid;             // Process ID
    int arrivalTime;     // Arrival Time
    int burstTime;       // Burst Time
    int completionTime;  // Completion Time
    int turnaroundTime;  // Turnaround Time
    int waitingTime;     // Waiting Time

    public Process(int pid, int arrivalTime, int burstTime) {
        this.pid = pid;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }

    @Override
    public int compareTo(Process other) {
        return this.arrivalTime - other.arrivalTime; // Sort by arrival time
    }
}

public class FCFS {
    public static void calculateTimes(Process[] processes) {
        int time = 0;

        for (Process process : processes) {
            if (time < process.arrivalTime) {
                time = process.arrivalTime;
            }
            time += process.burstTime;
            process.completionTime = time;
            process.turnaroundTime = process.completionTime - process.arrivalTime;
            process.waitingTime = process.turnaroundTime - process.burstTime;
        }
    }

    public static void printProcessTable(Process[] processes) {
        System.out.println("\n\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time");
        for (Process process : processes) {
            System.out.printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                    process.pid,
                    process.arrivalTime,
                    process.burstTime,
                    process.completionTime,
                    process.turnaroundTime,
                    process.waitingTime);
        }
    }

    public static void printGanttChart(Process[] processes) {
        System.out.println("\nGantt Chart:");
        System.out.print("|");
        for (Process process : processes) {
            System.out.printf(" P%d |", process.pid);
        }
        System.out.println();
        int time = 0;
        System.out.print("0");
        for (Process process : processes) {
            time = process.completionTime;
            System.out.printf("   %d", time);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        Process[] processes = new Process[n];

        for (int i = 0; i < n; i++) {
            System.out.printf("Enter arrival time for Process %d: ", i + 1);
            int arrivalTime = scanner.nextInt();
            System.out.printf("Enter burst time for Process %d: ", i + 1);
            int burstTime = scanner.nextInt();
            processes[i] = new Process(i + 1, arrivalTime, burstTime);
        }

        Arrays.sort(processes); // Sort processes by arrival time
        calculateTimes(processes);

        printProcessTable(processes);
        printGanttChart(processes);

        int totalTurnaroundTime = 0, totalWaitingTime = 0;
        for (Process process : processes) {
            totalTurnaroundTime += process.turnaroundTime;
            totalWaitingTime += process.waitingTime;
        }

        System.out.println("\nTotal Turnaround Time: " + totalTurnaroundTime);
        System.out.println("Total Waiting Time: " + totalWaitingTime);
        scanner.close();
    }
}
