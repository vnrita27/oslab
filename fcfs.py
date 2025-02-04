
def fcfs_scheduling():
    # Number of processes
    n = int(input("Enter the number of processes: "))
    
    # Lists to store the arrival time and burst time of each process
    processes = []
    
    # Getting input for arrival time and burst time for each process
    for i in range(n):
        at = int(input(f"Enter Arrival Time for Process P{i+1}: "))
        bt = int(input(f"Enter Burst Time for Process P{i+1}: "))
        processes.append({'arrival_time': at, 'burst_time': bt})
    
    # Initialize lists for completion time, turnaround time, and waiting time
    completion_time = [0] * n
    turnaround_time = [0] * n
    waiting_time = [0] * n
    
    # First process completes at its arrival time + burst time (since it starts at time 0)
    completion_time[0] = processes[0]['arrival_time'] + processes[0]['burst_time']
    
    # CT
    for i in range(1, n):
        # Completion time is either the previous process's completion time, or the current process's arrival time
        # whichever is greater, then add the current process's burst time
        completion_time[i] = max(completion_time[i-1], processes[i]['arrival_time']) + processes[i]['burst_time']
    
    # (TAT = CT - AT)
    for i in range(n):
        turnaround_time[i] = completion_time[i] - processes[i]['arrival_time']
    
    # (WT = TAT - BT)
    for i in range(n):
        waiting_time[i] = turnaround_time[i] - processes[i]['burst_time']
    
    # averages
    avg_tat = sum(turnaround_time) / n
    avg_wt = sum(waiting_time) / n
    
    # Print the results
    print("\nProcess | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time")
    for i in range(n):
        print(f"P{i+1}     | {processes[i]['arrival_time']}           | {processes[i]['burst_time']}         | {completion_time[i]}              | {turnaround_time[i]}              | {waiting_time[i]}")
    
    # Print the average
    print(f"\nAverage Turnaround Time (TAT): {avg_tat:.2f}")
    print(f"Average Waiting Time (WT): {avg_wt:.2f}")

# Call the function to run the program
fcfs_scheduling()
