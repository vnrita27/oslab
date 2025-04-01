class MemoryAllocation:
    def __init__(self, partitions, processes):
        self.partitions = partitions
        self.processes = processes
        self.partition_status = ['Free' for _ in partitions]
    
    # First Fit 
    def first_fit(self):
        allocation = [-1] * len(self.processes)
        for i, process_size in enumerate(self.processes):
            for j, partition_size in enumerate(self.partitions):
                if self.partition_status[j] == 'Free' and partition_size >= process_size:
                    allocation[i] = j
                    self.partition_status[j] = 'Occupied'
                    break
        return allocation

    # Worst Fit 
    def worst_fit(self):
        allocation = [-1] * len(self.processes)
        for i, process_size in enumerate(self.processes):
            worst_idx = -1
            worst_size = -1
            for j, partition_size in enumerate(self.partitions):
                if self.partition_status[j] == 'Free' and partition_size >= process_size:
                    if partition_size > worst_size:
                        worst_size = partition_size
                        worst_idx = j
            if worst_idx != -1:
                allocation[i] = worst_idx
                self.partition_status[worst_idx] = 'Occupied'
        return allocation

    # Best Fit 
    def best_fit(self):
        allocation = [-1] * len(self.processes)
        for i, process_size in enumerate(self.processes):
            best_idx = -1
            best_size = float('inf')
            for j, partition_size in enumerate(self.partitions):
                if self.partition_status[j] == 'Free' and partition_size >= process_size:
                    if partition_size < best_size:
                        best_size = partition_size
                        best_idx = j
            if best_idx != -1:
                allocation[i] = best_idx
                self.partition_status[best_idx] = 'Occupied'
        return allocation

partitions = [100, 500, 200, 300, 600]
processes = [212, 417, 112, 426]

allocator = MemoryAllocation(partitions, processes)

print("First Fit Allocation:", allocator.first_fit())

allocator.partition_status = ['Free' for _ in partitions]

print("Worst Fit Allocation:", allocator.worst_fit())

allocator.partition_status = ['Free' for _ in partitions]

print("Best Fit Allocation:", allocator.best_fit())
