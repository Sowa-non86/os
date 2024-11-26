import java.util.Scanner;

class Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int priority;   // Priority
    int finish;     // Finish Time
    int waiting;    // Waiting Time
    int total;      // Total Turnaround Time
    int remaining;  // Remaining Burst Time

    Process(int pid, int arrival, int burst, int priority) {
        this.pid = pid;
        this.arrival = arrival;
        this.burst = burst;
        this.priority = priority;
        this.remaining = burst; // Initialize remaining burst time
    }
}

public class PrioritySchedulingpreemetive {
    static final int MAX = 20;

    public static void calculateTimes(Process[] processes, int n, int[] ganttChart, int[] ganttSize) {
        int currentTime = 0, completed = 0;
        int minPriority, selectedProcess;

        ganttSize[0] = 0;

        while (completed < n) {
            minPriority = Integer.MAX_VALUE;
            selectedProcess = -1;

            // Find the process with the highest priority among those that have arrived
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival <= currentTime && processes[i].remaining > 0 && processes[i].priority < minPriority) {
                    minPriority = processes[i].priority;
                    selectedProcess = i;
                }
            }

            if (selectedProcess == -1) {
                // No process available, increment the current time
                currentTime++;
                continue;
            }

            // Execute the selected process for 1 unit of time
            ganttChart[ganttSize[0]++] = processes[selectedProcess].pid;
            currentTime++;
            processes[selectedProcess].remaining--;

            // If the process finishes
            if (processes[selectedProcess].remaining == 0) {
                processes[selectedProcess].finish = currentTime;
                processes[selectedProcess].total = processes[selectedProcess].finish - processes[selectedProcess].arrival;
                processes[selectedProcess].waiting = processes[selectedProcess].total - processes[selectedProcess].burst;
                completed++;
            }
        }
    }

    public static void printTable(Process[] processes, int n) {
        System.out.printf("%-12s %-13s %-11s %-10s %-12s %-10s %-12s%n", 
                          "Process_ID", "Arrival_Time", "Burst_Time", "Priority", "Finish_Time", "Total_Time", "Waiting_Time");
        for (int i = 0; i < n; i++) {
            System.out.printf("P%-11d %-13d %-11d %-10d %-12d %-10d %-12d%n",
                              processes[i].pid, processes[i].arrival, processes[i].burst, processes[i].priority, 
                              processes[i].finish, processes[i].total, processes[i].waiting);
        }
    }

    public static void printGanttChart(int[] ganttChart, int ganttSize) {
        System.out.println("\nGantt Chart:");
        
        // Consolidating consecutive time slots for the same process
        int[] startTimes = new int[MAX];
        int[] endTimes = new int[MAX];
        int[] consolidatedPids = new int[MAX];
        int consolidatedSize = 0;

        startTimes[0] = 0; // Start of the first process
        consolidatedPids[0] = ganttChart[0];

        for (int i = 1; i < ganttSize; i++) {
            if (ganttChart[i] != ganttChart[i - 1]) {
                endTimes[consolidatedSize] = i; // End of the current process
                consolidatedSize++;
                startTimes[consolidatedSize] = i; // Start of the new process
                consolidatedPids[consolidatedSize] = ganttChart[i];
            }
        }
        endTimes[consolidatedSize] = ganttSize; // End of the last process
        consolidatedSize++;

        // Print top border
        for (int i = 0; i < consolidatedSize; i++) {
            System.out.print(" ");
            for (int j = startTimes[i]; j < endTimes[i]; j++) {
                System.out.print("-");
            }
        }
        System.out.println();
        System.out.print("|");

        // Print process IDs
        for (int i = 0; i < consolidatedSize; i++) {
            int length = endTimes[i] - startTimes[i];
            System.out.print(" P" + consolidatedPids[i] + " ");
            for (int j = 1; j < length - 1; j++) {
                System.out.print(" ");
            }
            System.out.print("|");
        }

        // Print bottom border
        System.out.println();
        for (int i = 0; i < consolidatedSize; i++) {
            for (int j = startTimes[i]; j < endTimes[i]; j++) {
                System.out.print("-");
            }
        }

        // Print time labels
        System.out.println();
        System.out.print("0");
        for (int i = 0; i < consolidatedSize; i++) {
            System.out.print("   " + endTimes[i]);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();
        Process[] processes = new Process[n];
        int[] ganttChart = new int[100];
        int[] ganttSize = new int[1];

        for (int i = 0; i < n; i++) {
            System.out.printf("Enter arrival time, burst time, and priority of process P%d: ", i + 1);
            int arrival = scanner.nextInt();
            int burst = scanner.nextInt();
            int priority = scanner.nextInt();
            processes[i] = new Process(i + 1, arrival, burst, priority);
        }

        calculateTimes(processes, n, ganttChart, ganttSize);
        printTable(processes, n);
        printGanttChart(ganttChart, ganttSize[0]);

        scanner.close();
    }
}
