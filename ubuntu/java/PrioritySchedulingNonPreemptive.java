import java.util.Scanner;

class Process {
    int pid, arrivalTime, burstTime, finishTime, waitingTime, turnaroundTime, priority;
}

public class PrioritySchedulingNonPreemptive {

    public static void findTimes(Process[] proc, int n) {
        // Sort processes based on priority (lower number means higher priority)
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (proc[i].priority > proc[j].priority) {
                    Process temp = proc[i];
                    proc[i] = proc[j];
                    proc[j] = temp;
                }
            }
        }

        // Calculating times for each process
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

    public static void printGanttChart(Process[] proc, int n) {
        System.out.println("\nGantt Chart:");
        System.out.print("|");

        // Print process bars
        for (int i = 0; i < n; i++) {
            System.out.print("  P" + proc[i].pid + "  |");
        }

        System.out.println();

        // Print time labels
        int currentTime = proc[0].arrivalTime;
        System.out.print(currentTime);

        for (int i = 0; i < n; i++) {
            int endTime = proc[i].finishTime;
            int gap = String.valueOf(currentTime).length() + 6 - String.valueOf(endTime).length();
            for (int j = 0; j < gap; j++) {
                System.out.print(" ");
            }
            System.out.print(endTime);
            currentTime = endTime;
        }

        System.out.println();
    }

    public static void FCFS(Process[] proc, int n) {
        findTimes(proc, n);

        System.out.println("\nPID\tArrival\tBurst\tFinish\tTurnaround\tWaiting");
        for (Process p : proc) {
            System.out.printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", p.pid, p.arrivalTime, p.burstTime,
                    p.finishTime, p.turnaroundTime, p.waitingTime);
        }

        printGanttChart(proc, n);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter number of processes: ");
        int n = scanner.nextInt();
        Process[] proc = new Process[n];

        for (int i = 0; i < n; i++) {
            proc[i] = new Process();
            proc[i].pid = i + 1;

            System.out.printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
            proc[i].arrivalTime = scanner.nextInt();
            proc[i].burstTime = scanner.nextInt();
            proc[i].priority = scanner.nextInt();
        }

        FCFS(proc, n);
    }
}
