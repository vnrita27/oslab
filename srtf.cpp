#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MAX
using namespace std;

void srtf(int n, vector<int> &bt)
{
    vector<int> ct(n, 0), tat(n, 0), wt(n, 0);
    int total_tat = 0, total_wt = 0;

    // Vector to track the remaining burst times
    vector<int> rem_bt = bt;
    vector<bool> done(n, false); // To track if a process is completed
    int completed = 0, time = 0;

    // While there are processes remaining to be completed
    while (completed < n)
    {
        int min_time = INT_MAX;
        int curr_proc = -1;

        // Find the process with the minimum remaining burst time
        for (int i = 0; i < n; i++)
        {
            if (!done[i] && rem_bt[i] < min_time && rem_bt[i] > 0)
            {
                min_time = rem_bt[i];
                curr_proc = i;
            }
        }

        // Process the selected process for 1 unit of time
        rem_bt[curr_proc]--; // Decrement remaining burst time for the process
        time++;

        // If a process is completed, calculate completion time, turnaround time, and waiting time
        if (rem_bt[curr_proc] == 0)
        {
            done[curr_proc] = true;
            completed++;

            // Calculate completion time (CT)
            ct[curr_proc] = time;

            // Calculate turnaround time (TAT) = CT - AT (Assuming AT = 0)
            tat[curr_proc] = ct[curr_proc];

            // Calculate waiting time (WT) = TAT - BT
            wt[curr_proc] = tat[curr_proc] - bt[curr_proc];

            total_tat += tat[curr_proc];
            total_wt += wt[curr_proc];
        }
    }

    // Print the results
    cout << "\nP  | BT | CT | TAT | WT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " | " << bt[i] << "  | " << ct[i] << "  | " << tat[i] << "   | " << wt[i] << endl;
    }

    // Calculate and print averages
    cout << "\nAvg TAT: " << (float)total_tat / n << endl;
    cout << "Avg WT: " << (float)total_wt / n << endl;
}

int main()
{
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> bt(n);

    // Input burst time (BT) for each process
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for Process P" << i + 1 << ": ";
        cin >> bt[i];
    }

    srtf(n, bt);

    return 0;
}
