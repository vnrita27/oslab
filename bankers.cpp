#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& need, vector<vector<int>>& alloc, vector<int>& available, int numProcesses, int numResources) {
    vector<int> work = available;
    vector<bool> finish(numProcesses, false);
    int count = 0;

    while (count < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    for (int j = 0; j < numResources; j++) work[j] += alloc[i][j];
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

bool requestResources(vector<vector<int>>& max, vector<vector<int>>& alloc, vector<int>& available, vector<vector<int>>& need, int processID, vector<int>& request, int numResources) {
    for (int i = 0; i < numResources; i++) {
        if (request[i] > need[processID][i] || request[i] > available[i]) return false;
    }

    for (int i = 0; i < numResources; i++) {
        available[i] -= request[i];
        alloc[processID][i] += request[i];
        need[processID][i] -= request[i];
    }

    if (isSafe(need, alloc, available, max.size(), numResources)) return true;

    for (int i = 0; i < numResources; i++) {
        available[i] += request[i];
        alloc[processID][i] -= request[i];
        need[processID][i] += request[i];
    }
    return false;
}

int main() {
    int numProcesses = 5, numResources = 3;
    vector<vector<int>> max = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    vector<vector<int>> alloc = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    vector<int> available = {3, 3, 2};
    vector<vector<int>> need(numProcesses, vector<int>(numResources));

    for (int i = 0; i < numProcesses; i++) 
        for (int j = 0; j < numResources; j++) 
            need[i][j] = max[i][j] - alloc[i][j];

    vector<int> request = {1, 0, 2};
    int processID = 1;

    if (requestResources(max, alloc, available, need, processID, request, numResources)) 
        cout << "Request granted." << endl;
    else 
        cout << "Request denied." << endl;

    return 0;
}
