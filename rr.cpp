#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void rr(vector<int>& bt, vector<int>& rt, int n, int tq) {
    queue<int> q;

    vector<int> wt(n, 0);  // Wait time for each process
    vector<int> tat(n, 0); // Turnaround time for each process
    
    int totalWT = 0;
    int totalTAT = 0;

    // Start with all processes in the ready queue
    for (int i = 0; i < n; ++i) {
        q.push(i);
    }

    // Simulate round-robin scheduling
    while (!q.empty()) {
        int i = q.front();
        q.pop();

        if (rt[i] > tq) {
            // If process needs more time, execute for the time quantum
            rt[i] -= tq;
            // Add wait time for other processes
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    wt[j] += tq;
                }
            }
            q.push(i);  // Put the process back in the queue
        } else {
            // Process finishes execution
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    wt[j] += rt[i];
                }
            }
            tat[i] = wt[i] + bt[i];
            totalWT += wt[i];
            totalTAT += tat[i];
            rt[i] = 0;  // Process is finished
        }
    }

    // Display the results
    cout << "ID\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << "\n";
    }

    cout << "\nAvg WT: " << (float)totalWT / n << endl;
    cout << "Avg TAT: " << (float)totalTAT / n << endl;
}

int main() {
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> bt(n); // Burst time for each process
    vector<int> rt(n); // Remaining time for each process

    // Read process burst times
    for (int i = 0; i < n; ++i) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> bt[i];
        rt[i] = bt[i]; // Initialize remaining time to burst time
    }

    cout << "Enter time quantum: ";
    cin >> tq;

    rr(bt, rt, n, tq);

    return 0;
}
