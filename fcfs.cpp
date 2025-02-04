#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sjf_scheduling(int n, vector<int> &bt)
{
    vector<int> ct(n), tat(n), wt(n);
    int total_tat = 0, total_wt = 0;

    // Sort the processes based on burst time (Shortest Job First)
    vector<int> sorted_index(n);
    for (int i = 0; i < n; i++)
    {
        sorted_index[i] = i;
    }
    sort(sorted_index.begin(), sorted_index.end(), [&bt](int a, int b)
         { return bt[a] < bt[b]; });

    // Calculate Completion Time (CT)
    ct[sorted_index[0]] = bt[sorted_index[0]]; // First process
    for (int i = 1; i < n; i++)
    {
        ct[sorted_index[i]] = ct[sorted_index[i - 1]] + bt[sorted_index[i]];
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - 0;     // Assuming Arrival Time is always 0
        wt[i] = tat[i] - bt[i]; // WT = TAT - BT
        total_tat += tat[i];
        total_wt += wt[i];
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

    sjf_scheduling(n, bt);

    return 0;
}
