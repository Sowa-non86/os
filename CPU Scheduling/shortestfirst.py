import matplotlib.pyplot as plt

class Process:
    def __init__(self, pid, arrival_time, burst_time):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.completion_time = 0
        self.turnaround_time = 0
        self.waiting_time = 0

def sjf_preemptive(processes):
    current_time = 0
    completed = 0
    gantt = []

    while completed != len(processes):
        available_processes = [p for p in processes if p.arrival_time <= current_time and p.remaining_time > 0]
        if available_processes:
            shortest = min(available_processes, key=lambda x: x.remaining_time)
            start_time = current_time
            current_time += 1
            shortest.remaining_time -= 1
            gantt.append((shortest.pid, start_time, current_time))
            if shortest.remaining_time == 0:
                completed += 1
                shortest.completion_time = current_time
                shortest.turnaround_time = shortest.completion_time - shortest.arrival_time
                shortest.waiting_time = shortest.turnaround_time - shortest.burst_time

                print(f"Process {shortest.pid}: Completion Time = {shortest.completion_time}, "
                      f"Turnaround Time = {shortest.turnaround_time}, Waiting Time = {shortest.waiting_time}")
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
processes = [Process(1, 0, 5), Process(2, 1, 3), Process(3, 2, 4), Process(4, 4, 1)]
sjf_preemptive(processes)
