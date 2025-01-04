#include <stdio.h>

struct Process {
    int id;      // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time
    int ct;      // Completion Time
    int tat;     // Turnaround Time
    int wt;      // Waiting Time
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    float total_tat = 0, total_wt = 0;

    // Calculate completion time, turnaround time, and waiting time
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].at) {
            currentTime = processes[i].at; // If the CPU is idle
        }
        processes[i].ct = currentTime + processes[i].bt;
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        currentTime = processes[i].ct;

        total_tat += processes[i].tat;
        total_wt += processes[i].wt;
    }

    // Display process details
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].id, processes[i].at, processes[i].bt, 
               processes[i].ct, processes[i].tat, processes[i].wt);
    }

    // Display average turnaround time and waiting time
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    // Sort processes by arrival time (FCFS assumes sorted order of arrival)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculateTimes(processes, n);

    return 0;
}

