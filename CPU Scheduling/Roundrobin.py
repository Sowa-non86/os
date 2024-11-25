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

def round_robin(processes, time_quantum):
    queue = []
    current_time = 0
    gantt = []

    while processes or queue:
        while processes and processes[0].arrival_time <= current_time:
            queue.append(processes.pop(0))

        if queue:
            process = queue.pop(0)
            start_time = current_time

            if process.remaining_time <= time_quantum:
                current_time += process.remaining_time
                process.remaining_time = 0
                process.completion_time = current_time
                process.turnaround_time = process.completion_time - process.arrival_time
                process.waiting_time = process.turnaround_time - process.burst_time
                gantt.append((process.pid, start_time, current_time))

                print(f"Process {process.pid}: Completion Time = {process.completion_time}, "
                      f"Turnaround Time = {process.turnaround_time}, Waiting Time = {process.waiting_time}")
            else:
                current_time += time_quantum
                process.remaining_time -= time_quantum
                queue.append(process)
                gantt.append((process.pid, start_time, current_time))
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
processes = [Process(1, 0, 5), Process(2, 1, 4), Process(3, 2, 2), Process(4, 4, 1)]
round_robin(processes, 1)
