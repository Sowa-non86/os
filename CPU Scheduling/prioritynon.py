import matplotlib.pyplot as plt

class Process:
    def __init__(self, pid, arrival_time, burst_time, priority):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.priority = priority
        self.completion_time = 0
        self.turnaround_time = 0
        self.waiting_time = 0

def priority_non_preemptive(processes):
    processes.sort(key=lambda x: (x.arrival_time, x.priority))
    current_time = 0
    gantt = []

    while processes:
        available_processes = [p for p in processes if p.arrival_time <= current_time]
        if available_processes:
            process = min(available_processes, key=lambda x: x.priority)
            processes.remove(process)
            start_time = current_time
            current_time += process.burst_time
            process.completion_time = current_time
            process.turnaround_time = process.completion_time - process.arrival_time
            process.waiting_time = process.turnaround_time - process.burst_time
            gantt.append((process.pid, start_time, current_time))

            print(f"Process {process.pid}: Completion Time = {process.completion_time}, "
                  f"Turnaround Time = {process.turnaround_time}, Waiting Time = {process.waiting_time}")
        else:
            current_time += 1

    draw_gantt_chart(gantt)

def draw_gantt_chart(gantt):
    fig, gnt = plt.subplots()
    gnt.set_xlabel('Time')
    gnt.set_ylabel('Process ID')
    gnt.set_yticks([i for i in range(len(gantt))])
    gnt.set_yticklabels([f'P{g[0]}' for g in gantt])
    for idx, (pid, start, end) in enumerate(gantt):
        gnt.broken_barh([(start, end - start)], (idx - 0.4, 0.8), facecolors='tab:blue')
    plt.show()

# Example
processes = [Process(1, 0, 10, 2), Process(2, 2, 5, 1), Process(3, 3, 2, 0), Process(4, 5, 20, 3)]
priority_non_preemptive(processes)
