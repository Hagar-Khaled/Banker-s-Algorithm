#include <bits/stdc++.h>
using namespace std;

#define PN 5 // Number of processes
#define RN 3 // Number of resources

int alloc[PN][RN];
int maximum[PN][RN];
int available[RN];
int need[PN][RN];
int request[RN + 1];
int p, r;

// Utility function to print matrices
void print_matrix(const string& title, int matrix[PN][RN]) {
    cout << "\n" << title << ":\n\t";
    for (int r = 0; r < RN; r++) cout << "R" << r << "\t";
    cout << "\n";
    for (int p = 0; p < PN; p++) {
        cout << "P" << p << "\t";
        for (int r = 0; r < RN; r++) cout << matrix[p][r] << "\t";
        cout << "\n";
    }
}

// Calculate need matrix
void calculate_need() {
    for (p = 0; p < PN; p++)
        for (r = 0; r < RN; r++)
            need[p][r] = maximum[p][r] - alloc[p][r];
    print_matrix("Need Matrix", need);
}

// Safety algorithm
bool is_safe(bool verbose = true) {
    int finish[PN] = {0}, tempavail[RN];
    int counter = 0;
    for (r = 0; r < RN; r++) tempavail[r] = available[r];

    if (verbose) cout << "\nSafe sequence check:\n";

    bool progress;
    do {
        progress = false;
        for (p = 0; p < PN; p++) {
            if (!finish[p]) {
                bool can_run = true;
                for (r = 0; r < RN; r++) {
                    if (need[p][r] > tempavail[r]) {
                        can_run = false;
                        break;
                    }
                }
                if (can_run) {
                    for (r = 0; r < RN; r++)
                        tempavail[r] += alloc[p][r];
                    finish[p] = 1;
                    counter++;
                    if (verbose) {
                        cout << "P" << p << " runs. Available: ";
                        for (r = 0; r < RN; r++) cout << tempavail[r] << " ";
                        cout << "\n";
                    }
                    progress = true;
                }
            }
        }
    } while (progress);

    if (counter == PN) {
        if (verbose) cout << "\nSystem is in a SAFE state.\n";
        return true;
    } else {
        if (verbose) cout << "\nSystem is in an UNSAFE state!\n";
        return false;
    }
}

// Handle resource request
bool test_safe() {
    int tp = request[0];
    int tempneed[RN], tempalloc[RN], tempavail[RN];
    for (r = 0; r < RN; r++) {
        if (request[r + 1] > need[tp][r]) {
            cout << "\nError: Process requested more than its need.\n";
            return false;
        }
        if (request[r + 1] > available[r]) {
            cout << "\nRequest cannot be granted now. Not enough resources.\n";
            return false;
        }
    }

    for (r = 0; r < RN; r++) {
        tempneed[r] = need[tp][r];
        tempalloc[r] = alloc[tp][r];
        tempavail[r] = available[r];

        need[tp][r] -= request[r + 1];
        alloc[tp][r] += request[r + 1];
        available[r] -= request[r + 1];
    }

    bool safe = is_safe(false);
    if (safe) {
        cout << "\nRequest granted. System remains in a SAFE state.\n";
    } else {
        cout << "\nRequest denied. System would become UNSAFE.\n";
        for (r = 0; r < RN; r++) {
            need[tp][r] = tempneed[r];
            alloc[tp][r] = tempalloc[r];
            available[r] = tempavail[r];
        }
    }
    return safe;
}

// Manual entry from user
void manual_input() {
    cout << "\nEnter Allocation Matrix (5 processes x 3 resources):\n";
    for (p = 0; p < PN; p++) {
        cout << "P" << p << ": ";
        for (r = 0; r < RN; r++) cin >> alloc[p][r];
    }

    cout << "\nEnter Maximum Matrix (5 processes x 3 resources):\n";
    for (p = 0; p < PN; p++) {
        cout << "P" << p << ": ";
        for (r = 0; r < RN; r++) cin >> maximum[p][r];
    }

    cout << "\nEnter Available Resources (3 resources): ";
    for (r = 0; r < RN; r++) cin >> available[r];
}

// Initialization: default, random, or manual
void initialize(int mode) {
    if (mode == 1) {
        // Default
        int def_alloc[PN][RN] = {
            {0, 2, 0},
            {2, 0, 0},
            {3, 0, 2},
            {2, 1, 1},
            {0, 0, 2}};
        int def_max[PN][RN] = {
            {7, 5, 3},
            {3, 2, 2},
            {9, 0, 2},
            {2, 2, 2},
            {4, 3, 3}};
        int def_avail[RN] = {3, 2, 2};

        memcpy(alloc, def_alloc, sizeof(alloc));
        memcpy(maximum, def_max, sizeof(maximum));
        memcpy(available, def_avail, sizeof(available));
    } else if (mode == 2) {
        // Random
        srand(time(0));
        for (p = 0; p < PN; p++) {
            for (r = 0; r < RN; r++) {
                maximum[p][r] = rand() % 10 + 1;
                alloc[p][r] = rand() % (maximum[p][r] + 1);
            }
        }
        for (r = 0; r < RN; r++)
            available[r] = rand() % 6 + 1;
    } else {
        // Manual
        manual_input();
    }

    print_matrix("Allocation Matrix", alloc);
    print_matrix("Maximum Matrix", maximum);
    cout << "\nAvailable Resources: ";
    for (int i = 0; i < RN; i++) cout << available[i] << " ";
    cout << "\n";
}

int main() {
    cout << "=== Banker's Algorithm ===\n";
    cout << "Enter input mode:\n";
    cout << "1. Use default values\n";
    cout << "2. Use random values\n";
    cout << "3. Enter values manually\n";
    cout << "Choice: ";
    int mode;
    cin >> mode;

    initialize(mode);
    calculate_need();
    is_safe();

    cout << "\nEnter a resource request (Process ID followed by R0 R1 R2):\n";
    for (int i = 0; i < RN + 1; i++) cin >> request[i];

    test_safe();

    return 0;
}
