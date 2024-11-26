import java.util.*;

class Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;

    Process(int pid, int arrivalTime, int burstTime) {
        this.pid = pid;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.remainingTime = burstTime;
        this.completionTime = 0;
        this.waitingTime = 0;
        this.turnaroundTime = 0;
    }
}

public class RoundRobinScheduling {
    // Round Robin scheduling algorithm
    public static List<int[]> roundRobin(List<Process> processes, int quantum) {
        int time = 0;
        Queue<Process> queue = new LinkedList<>();
        List<int[]> ganttChart = new ArrayList<>();

        processes.sort(Comparator.comparingInt(p -> p.arrivalTime)); // Sort by arrival time
        queue.addAll(processes);

        while (!queue.isEmpty()) {
            Process process = queue.poll();
            if (process.remainingTime > quantum) {
                ganttChart.add(new int[]{process.pid, time, time + quantum});
                time += quantum;
                process.remainingTime -= quantum;
                queue.add(process);
            } else if (process.remainingTime > 0) {
                ganttChart.add(new int[]{process.pid, time, time + process.remainingTime});
                time += process.remainingTime;
                process.remainingTime = 0;
                process.completionTime = time;
                process.turnaroundTime = process.completionTime - process.arrivalTime;
                process.waitingTime = process.turnaroundTime - process.burstTime;
            }
        }
        return ganttChart;
    }

    // Function to display waiting time and turnaround time
    public static void displayTimes(List<Process> processes) {
        System.out.println("\nProcess\tArrival\tBurst\tWaiting\tTurnaround");
        for (Process process : processes) {
            System.out.printf("P%d\t%d\t%d\t%d\t%d\n",
                    process.pid, process.arrivalTime, process.burstTime, process.waitingTime, process.turnaroundTime);
        }
    }

    // Print Gantt Chart in the console
    public static void printGanttChart(List<int[]> ganttChart) {
        System.out.println("\nGantt Chart:");
        for (int[] entry : ganttChart) {
            System.out.printf("| P%d ", entry[0]);
        }
        System.out.println("|");

        int lastTime = 0;
        for (int[] entry : ganttChart) {
            System.out.printf("%d\t", entry[1]);
            lastTime = entry[2];
        }
        System.out.printf("%d\n", lastTime);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<Process> processes = new ArrayList<>();

        System.out.print("Enter the number of processes: ");
        int numProcesses = scanner.nextInt();

        for (int i = 1; i <= numProcesses; i++) {
            System.out.println("Enter details for Process " + i + ":");
            System.out.print("Arrival Time: ");
            int arrivalTime = scanner.nextInt();
            System.out.print("Burst Time: ");
            int burstTime = scanner.nextInt();
            processes.add(new Process(i, arrivalTime, burstTime));
        }

        System.out.print("Enter the Time Quantum for Round Robin: ");
        int quantum = scanner.nextInt();

        System.out.println("\nPreset Processes:");
        System.out.println("PID\tArrival Time\tBurst Time");
        for (Process process : processes) {
            System.out.printf("%d\t%d\t\t%d\n",
                    process.pid, process.arrivalTime, process.burstTime);
        }

        System.out.println("\n--- Round Robin ---");
        List<int[]> ganttChartRR = roundRobin(processes, quantum);
        displayTimes(processes);
        printGanttChart(ganttChartRR);

        scanner.close();
    }
}
