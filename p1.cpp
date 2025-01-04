#include <stdio.h>
#include <stdbool.h>

void calculateNeed(int need[][10], int max[][10], int allocation[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int processes[], int available[], int max[][10], int allocation[][10], int n, int m) {
    int need[10][10];
    calculateNeed(need, max, allocation, n, m);

    bool finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int safeSequence[n];
    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[p][k];
                    }

                    safeSequence[count++] = processes[p];
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int processes[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    int allocation[n][10], max[n][10], available[m];

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    isSafe(processes, available, max, allocation, n, m);
    return 0;
}

